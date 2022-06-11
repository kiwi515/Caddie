#ifndef CADDIE_CORE_INPUT_MGR_H
#define CADDIE_CORE_INPUT_MGR_H
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Controller input manager
 */
class InputMgr {
public:
    enum EPlayer { PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4, PLAYER_MAX };

    enum EButton {
        BTN_NONE = 0x0000,
        BTN_LEFT = 0x0001,
        BTN_RIGHT = 0x0002,
        BTN_DOWN = 0x0004,
        BTN_UP = 0x0008,
        BTN_PLUS = 0x0010,
        BTN_2 = 0x0100,
        BTN_1 = 0x0200,
        BTN_B = 0x0400,
        BTN_A = 0x0800,
        BTN_MINUS = 0x1000,
        BTN_HOME = 0x8000,

        BTN_DPAD_ALL = BTN_LEFT | BTN_RIGHT | BTN_DOWN | BTN_UP
    };

public:
    static InputMgr& GetInstance() {
        static InputMgr instance;
        return instance;
    }

    void Calc();

    u32 Held(EPlayer player) const {
        CADDIE_ASSERT(player < PLAYER_MAX);
        return mBtnHeld[player];
    }

    u32 Trig(EPlayer player) const {
        CADDIE_ASSERT(player < PLAYER_MAX);
        return mBtnTrig[player];
    }

    u32 Released(EPlayer player) const {
        CADDIE_ASSERT(player < PLAYER_MAX);
        return mBtnReleased[player];
    }

private:
    InputMgr() {}
    virtual ~InputMgr() {}

private:
    //! @brief Buttons being held
    u32 mBtnHeld[PLAYER_MAX];
    //! @brief Buttons pressed this frame
    u32 mBtnTrig[PLAYER_MAX];
    //! @brief Buttons released
    u32 mBtnReleased[PLAYER_MAX];
};

} // namespace caddie

#endif
