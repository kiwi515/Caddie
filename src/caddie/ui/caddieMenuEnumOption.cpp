#include "caddieMenuEnumOption.h"

namespace caddie
{
    void MenuEnumOption::Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow) const
    {
        // Option name
        Sp2::PrintOutline(GetName(), color, shadow, false, x, y);

        // Option value
        Sp2::PrintOutline((IsEnabled() ? mTable[GetValue()] : "DISABLED"), (IsEnabled() ? color : COLOR_DISABLED), shadow, false, x + gapX, y);
    }
}