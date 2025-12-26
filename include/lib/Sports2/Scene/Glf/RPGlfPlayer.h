#ifndef RP_SPORTS_GLF_PLAYER_H
#define RP_SPORTS_GLF_PLAYER_H
#include "types_caddie.h"
#include "types_sp2.h"

#include <nw4r/math.h>

class RPGlfBall;

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

    const nw4r::math::VEC2& GetAvatarAngle() const { return mAvatarAngle; }
    const nw4r::math::VEC3& GetAvatarPos() const { return mAvatarPos; }

    u16 GetPrevGndAttr() const { return mPrevGndAttr; }

    RPGlfBall* GetBall() const { return mpGlfBall; }

    u32 GetWord0x44() const { return WORD_0x44; }

private:
    char UNK_0x4[0x44 - 0x4];
    u32 WORD_0x44; // at 0x44
    char UNK_0x48[0x84 - 0x48];
    nw4r::math::VEC2 mAvatarAngle; // at 0x84
    char UNK_0x8C[0x98 - 0x8C];
    nw4r::math::VEC3 mAvatarPos; // at 0x98
    char UNK_0xA4[0xB0 - 0xA4];
    u16 mPrevGndAttr; // at 0xB0
    char UNK_0xB2[0xC0 - 0xB2];
    u32 mStroke;             // at 0xC0
    u32 mStrokeAfterPenalty; // at 0xC4
    char UNK_0xC8[0xD0 - 0xC8];
    RPGlfBall* mpGlfBall; // at 0xD0
    char UNK_0xD4[0x198 - 0xD4];
};

#endif
