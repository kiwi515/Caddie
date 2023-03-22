#ifndef SP2_DRAW_MGR_H
#define SP2_DRAW_MGR_H
#include "types_caddie.hpp"

namespace Sp2 {

class DrawMgr {
public:
    enum DrawPass {
        DrawPass_0,
        DrawPass_1,
        DrawPass_DrawBefore,
        DrawPass_Draw2D,
        DrawPass_4,
        DrawPass_5,
        DrawPass_Draw,
        DrawPass_DrawXLU,
    };

public:
    static DrawMgr& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    static DrawPass getDrawPass() { return static_cast<DrawPass>(sDrawPass); }

private:
    char _00[0x18];
    u32 mSequence;

    static u32 sDrawPass;
    static DrawMgr* sInstance;
};

} // namespace Sp2

#endif
