#include "caddieMenuActionOption.h"

#include <Sp2Util.h>

namespace caddie
{
    void MenuActionOption::Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow) const
    {
        // Action options do not have a setting to draw
        Sp2::PrintOutline(GetName(), color, shadow, false, x, y);
    }
}