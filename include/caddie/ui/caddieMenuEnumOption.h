#ifndef CADDIE_UI_MENU_ENUM_OPTION_H
#define CADDIE_UI_MENU_ENUM_OPTION_H
#include "types_caddie.h"
#include "caddieMenuIntOption.h"

#include <Sp2Util.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuEnumOption : public MenuIntOption
    {
    public:
        MenuEnumOption(const char *name, int min, int max, const char **table) : MenuIntOption(name, min, max), mTable(table) {}
        virtual ~MenuEnumOption() {}
        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

        void SetTable(const char **table) { mTable = table; }

    private:
        const char **mTable;
    };
}

#endif