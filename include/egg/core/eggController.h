#ifndef EGG_CORE_CONTROLLER_H
#define EGG_CORE_CONTROLLER_H
#include "types_egg.h"

namespace EGG
{
    enum eButtonType
    {
        BTN_NONE  = 0x0000,
        BTN_LEFT  = 0x0001,
        BTN_RIGHT = 0x0002,
        BTN_DOWN  = 0x0004,
        BTN_UP    = 0x0008,
        BTN_PLUS  = 0x0010,
        BTN_2     = 0x0100,
        BTN_1     = 0x0200,
        BTN_B     = 0x0400,
        BTN_A     = 0x0800,
        BTN_MINUS = 0x1000,
        BTN_HOME  = 0x8000,
    };

    class CoreController
    {
    public:
        inline u16 getButtons() const
        {
            return mButtons;
        }

    private:
        char UNK_0x0[0x1A];
        u16 mButtons; // at 0x1A
        // . . .
    };

    class CoreControllerMgr
    {
    public:
        static CoreControllerMgr& getInstance() 
        {
            CADDIE_ASSERT(sInstance != NULL);
            return *sInstance;
        }

        CoreController *getNthController(int i);

    private:
        static CoreControllerMgr *sInstance;
    };
}

#endif