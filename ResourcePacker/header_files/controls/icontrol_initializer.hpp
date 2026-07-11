#ifndef RES_PACK_ICONTROL_INITIALIZER_HPP
#define RES_PACK_ICONTROL_INITIALIZER_HPP

class IControlInitializer
{
    protected:
        virtual void _i_init_controls() = 0;
        virtual void _i_connect_internal_events() = 0;
        virtual void _i_connect_external_events() = 0;
        virtual void _i_update_pack_data() {};
};

#endif // RES_PACK_ICONTROL_INITIALIZER_HPP