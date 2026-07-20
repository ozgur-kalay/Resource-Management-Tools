#include <iostream>
#include <string>
#include <vector>
#include "event_system.hpp"

class PlayerDamagedEvent
    : public EventSystem::Event<PlayerDamagedEvent, int>
{
};

class EnemyDamagedEvent
    : public EventSystem::Event<EnemyDamagedEvent, int, const std::string&>
{
};

class GameStartedEvent
    : public EventSystem::Event<GameStartedEvent>
{
};

void on_game_started()
{
    std::cout << "Free function: Game started\n";
}

class Player
{
    public:
        void take_damage(int damage)
        {
            std::cout << "Player emits PlayerDamagedEvent\n";
            m_damaged_event.emit(damage);
        }

    private:
        PlayerDamagedEvent m_damaged_event;
};

class Enemy
{
    public:
        void take_damage(int damage, const std::string& name)
        {
            std::cout << "Enemy emits EnemyDamagedEvent\n";
            m_damaged_event.emit(damage, name);
        }

    private:
        EnemyDamagedEvent m_damaged_event;
};

class Game
{
    public:
        void start()
        {
            m_started_event.emit();
        }

    private:
        GameStartedEvent m_started_event;
};

class Interface
{
    public:
        Interface()
        {
            auto& manager = EventSystem::EventManager::get_instance();

            m_player_damaged_subscription =
                manager.subscribe<PlayerDamagedEvent>(
                    this,
                    &Interface::on_player_damaged
                );

            m_enemy_damaged_subscription =
                manager.subscribe<EnemyDamagedEvent>(
                    this,
                    &Interface::on_enemy_damaged
                );
        }

    private:
        EventSystem::Subscription m_player_damaged_subscription;
        EventSystem::Subscription m_enemy_damaged_subscription;

        void on_player_damaged(int damage)
        {
            std::cout << "Member function: Player took "
                      << damage << " damage\n";
        }

        void on_enemy_damaged(int damage, const std::string& name)
        {
            std::cout << "Member function: " << name
                      << " took " << damage << " damage\n";
        }
};

int main()
{
    auto& manager = EventSystem::EventManager::get_instance();

    // Free-function subscription.
    EventSystem::Subscription game_started_subscription =
        manager.subscribe<GameStartedEvent>(&on_game_started);

    // Lambda subscription.
    EventSystem::Subscription lambda_subscription =
        manager.subscribe<PlayerDamagedEvent>(
            [](int damage)
            {
                std::cout << "Lambda: Player damage = "
                          << damage << '\n';
            }
        );

    Player player;
    Enemy enemy;
    Game game;

    {
        Interface interface;

        player.take_damage(100);
        enemy.take_damage(25, "Goblin");
        game.start();

        std::cout << "\nDestroying Interface...\n";
    }

    // Interface subscriptions were automatically removed.
    std::cout << "\nEmitting after Interface destruction:\n";

    player.take_damage(50);
    enemy.take_damage(10, "Orc");
    game.start();

    // Manual early disconnection.
    std::cout << "\nDisconnecting lambda...\n";
    lambda_subscription.disconnect();

    player.take_damage(20);

    std::cout << "\nLambda connected: "
              << std::boolalpha
              << lambda_subscription.is_connected()
              << '\n';

    return 0;
}