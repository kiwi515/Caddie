#ifndef RP_SPORTS_GLF_PLAYER_MANAGER_H
#define RP_SPORTS_GLF_PLAYER_MANAGER_H
#include "RPGlfPlayer.h"
#include "caddieAssert.h"
#include "types_Sp2.h"

#include <Scene/Glf/Sp2GlfDefine.h>

/**
 * @brief Golf player manager
 */
class RPGlfPlayerManager {
public:
    static RPGlfPlayerManager& GetInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    RPGlfPlayer& GetPlayer(int i) {
        CADDIE_ASSERT(i < Sp2::Glf::PLAYER_MAX);
        return mPlayers[i];
    }

    const RPGlfPlayer& GetPlayer(int i) const {
        CADDIE_ASSERT(i < Sp2::Glf::PLAYER_MAX);
        return mPlayers[i];
    }

    RPGlfPlayer& GetCurrentPlayer() { return mPlayers[mCurrentPlayerID]; }

    const RPGlfPlayer& GetCurrentPlayer() const {
        return mPlayers[mCurrentPlayerID];
    }

    u32 GetCurrentPlayerID() const { return mCurrentPlayerID; }

private:
    RPGlfPlayerManager();
    virtual ~RPGlfPlayerManager();

public:
    RPGlfPlayer mPlayers[Sp2::Glf::PLAYER_MAX]; // at 0x4
    char UNK_0x664[0x690 - 0x664];
    u32 mCurrentPlayerID; // at 0x690

    static RPGlfPlayerManager* sInstance;
};

#endif
