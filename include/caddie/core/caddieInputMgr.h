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
