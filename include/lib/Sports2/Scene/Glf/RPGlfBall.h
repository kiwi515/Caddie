#ifndef RP_SPORTS_GLF_BALL_H
#define RP_SPORTS_GLF_BALL_H
#include "RPGlfCollisionModel.h"
#include "RPGlfMapObjBase.h"
#include "types_sp2.h"

class RPGlfBall : public RPGlfMapObjBase {
public:
    RPGlfBall();
    virtual ~RPGlfBall();

    void Calc(u32 frame);

    u32 GetLifetime() const { return mLifetime; }
    void SetLifetime(u32 time) { mLifetime = time; }

    bool IsMoving() const { return mIsMoving; }
    void SetMoving(bool move) { mIsMoving = move; }

    RPGlfCollisionModel::ECollision GetCollision() const {
        return (RPGlfCollisionModel::ECollision)mCollision;
    }
    void SetCollision(RPGlfCollisionModel::ECollision col) { mCollision = col; }

    RPGlfCollisionModel::ECollision GetCollisionNoAir() const {
        return (RPGlfCollisionModel::ECollision)mCollisionNoAir;
    }
    void SetCollisionNoAir(RPGlfCollisionModel::ECollision col) {
        mCollisionNoAir = col;
    }

private:
    char UNK_0x50[0x4];
    u32 mLifetime; // at 0x54
    char UNK_0x58[0x60 - 0x58];
    bool mIsMoving; // at 0x60
    char UNK_0x61[0xB4 - 0x61];
    u16 mCollision;      // at 0xB4
    u16 mCollisionNoAir; // at 0xB6
    char UNK_0xB8[0x1E0 - 0xB8];
};

#endif
