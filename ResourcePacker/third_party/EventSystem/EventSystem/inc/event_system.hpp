#pragma once
#include <algorithm>
#include <any>
#include <cstddef>
#include <functional>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace EventSystem
{
    class EventManager;

    class Subscription
    {
        public:
            Subscription() = default;

            explicit Subscription(std::function<void()> disconnect_function): m_disconnect_function(std::move(disconnect_function)){}

            ~Subscription()
            {
                disconnect();
            }

            Subscription(const Subscription&) = delete;
            Subscription& operator=(const Subscription&) = delete;

            Subscription(Subscription&& other) noexcept : m_disconnect_function(std::move(other.m_disconnect_function))
            {
                other.m_disconnect_function = {};
            }

            Subscription& operator=(Subscription&& other) noexcept
            {
                if (this == &other)
                    return *this;

                disconnect();

                m_disconnect_function = std::move(other.m_disconnect_function);
                other.m_disconnect_function = {};

                return *this;
            }

            void disconnect()
            {
                if (!m_disconnect_function)
                    return;

                auto disconnect_function = std::move(m_disconnect_function);
                m_disconnect_function = {};
                disconnect_function();
            }

            bool is_connected() const
            {
                return static_cast<bool>(m_disconnect_function);
            }

        private:
            std::function<void()> m_disconnect_function;
    };

    template<typename EventType, typename... Args>
    class Event
    {
        public:
            using Callback = std::function<void(Args...)>;

            Event()
            {
                register_event();
            }

            void emit(Args... args);

        private:
            void register_event();
    };

    class EventManager
    {
        private:
            template<typename EventType>
            struct Channel
            {
                using Callback = typename EventType::Callback;

                struct Entry
                {
                    std::size_t id;
                    Callback callback;
                };

                std::size_t next_id = 1;
                std::vector<Entry> entries;
            };

        public:
            static EventManager& get_instance();

            EventManager(const EventManager&) = delete;
            EventManager& operator=(const EventManager&) = delete;
            EventManager(EventManager&&) = delete;
            EventManager& operator=(EventManager&&) = delete;

            template<typename EventType>
            void register_event()
            {
                std::type_index event_type = typeid(EventType);

                if (!m_events.contains(event_type))
                    m_events.emplace(
                        event_type,
                        std::make_shared<Channel<EventType>>()
                    );
            }

            template<typename EventType, typename Callback>
            Subscription subscribe(Callback&& callback)
            {
                using EventCallback = typename EventType::Callback;

                auto channel = get_channel<EventType>();
                std::size_t subscription_id = channel->next_id++;

                channel->entries.push_back({
                    subscription_id,
                    EventCallback(std::forward<Callback>(callback))
                });

                std::weak_ptr<Channel<EventType>> weak_channel = channel;

                return Subscription(
                    [weak_channel, subscription_id]()
                    {
                        auto locked_channel = weak_channel.lock();

                        if (!locked_channel)
                            return;

                        auto& entries = locked_channel->entries;

                        std::erase_if(
                            entries,
                            [subscription_id](const auto& entry)
                            {
                                return entry.id == subscription_id;
                            }
                        );
                    }
                );
            }

            template<typename EventType, typename Object, typename... Args>
            Subscription subscribe(
                Object* object,
                void (Object::*member_function)(Args...)
            )
            {
                return subscribe<EventType>(
                    [object, member_function](Args... args)
                    {
                        (object->*member_function)(
                            std::forward<Args>(args)...
                        );
                    }
                );
            }

            template<typename EventType, typename Object, typename... Args>
            Subscription subscribe(
                Object* object,
                void (Object::*member_function)(Args...) const
            )
            {
                return subscribe<EventType>(
                    [object, member_function](Args... args)
                    {
                        (object->*member_function)(
                            std::forward<Args>(args)...
                        );
                    }
                );
            }

            template<typename EventType, typename... Args>
            void emit_event(Args&&... args)
            {
                auto channel = get_channel<EventType>();

                std::vector<typename EventType::Callback> callbacks;
                callbacks.reserve(channel->entries.size());

                for (const auto& entry : channel->entries)
                    callbacks.push_back(entry.callback);

                for (auto& callback : callbacks)
                    callback(std::forward<Args>(args)...);
            }

            template<typename EventType>
            bool is_registered() const
            {
                return m_events.contains(typeid(EventType));
            }

        private:
            EventManager() = default;
            ~EventManager() = default;

            std::unordered_map<std::type_index, std::any> m_events;

            template<typename EventType>
            std::shared_ptr<Channel<EventType>> get_channel()
            {
                register_event<EventType>();

                return std::any_cast<
                    std::shared_ptr<Channel<EventType>>
                >(m_events.at(typeid(EventType)));
            }
    };

    template<typename EventType, typename... Args>
    void Event<EventType, Args...>::register_event()
    {
        static_assert(
            std::is_base_of_v<Event<EventType, Args...>, EventType>,
            "EventType must inherit from Event<EventType, Args...>"
        );

        EventManager::get_instance().register_event<EventType>();
    }

    template<typename EventType, typename... Args>
    void Event<EventType, Args...>::emit(Args... args)
    {
        EventManager::get_instance().emit_event<EventType>(
            std::forward<Args>(args)...
        );
    }
}