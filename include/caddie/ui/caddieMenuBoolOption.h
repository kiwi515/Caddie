#ifndef CADDIE_UI_MENU_BOOL_OPTION_H
#define CADDIE_UI_MENU_BOOL_OPTION_H
#include "types_caddie.h"
#include "caddieMenuIntOption.h"

#include <Sp2Util.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuBoolOption : public MenuIntOption
    {
    public:
        MenuBoolOption(const char *name) : MenuIntOption(name, 0, 1) {}
        virtual ~MenuBoolOption() {}
        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

    private:

    };
}

#endif