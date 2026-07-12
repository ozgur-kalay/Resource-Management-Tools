#ifndef RES_PACKER_CONFIG_HPP
#define RES_PACKER_CONFIG_HPP
#include "wx/wx.h"

namespace Config
{
    namespace Sizes
    {
        const wxSize WINDOW(1500, 800);
        const wxSize RESOURCE_LIST(WINDOW.x - 50, WINDOW.y - 300);
    }

    namespace Positions
    {
        const wxPoint RESOURCE_LIST(10, 10);
    }

}

#endif // RES_PACKER_CONFIG_HPP