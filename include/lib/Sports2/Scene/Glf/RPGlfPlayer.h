#ifndef RP_SPORTS_GLF_PLAYER_H
#define RP_SPORTS_GLF_PLAYER_H
#include "types_sp2.h"

/**
 * @brief Golf player
 */
class RPGlfPlayer {
public:
    RPGlfPlayer();
    virtual ~RPGlfPlayer();

    u32 GetStroke() const { return mStroke; }
    void SetStroke(u32 stroke) { mStroke = stroke; }

    u32 GetStrokeAfterPenalty() const { return mStrokeAfterPenalty; }
    void SetStrokeAfterPenalty(u32 stroke) { mStrokeAfterPenalty = stroke; }

private:
    char UNK_0x4[0xC0 - 0x4];
    u32 mStroke;             // at 0xC0
    u32 mStrokeAfterPenalty; // at 0xC4
    char UNK_0xC8[0x198 - 0xC8];
};

#endif
