#ifndef RP_SPORTS_GLF_COLLISION_MODEL_H
#define RP_SPORTS_GLF_COLLISION_MODEL_H
#include "types_Sp2.h"

/**
 * @brief KCL wrapper designed for the Golf scene
 */
class RPGlfCollisionModel {
public:
    //! @brief Collision types
    enum ECollision {
        COL_NONE,
        COL_FAIRWAY,
        COL_ROUGH,
        COL_BUNKER,
        COL_OB,
        COL_OB2,
        COL_GREEN,
        COL_WATER,
        COL_WOOD,
        COL_GREEN_EDGE,
        COL_SIDE_OF_CUP,
        COL_CUP,
        COL_ROCK_WALL,
        COL_VALLEY,
        COL_GLASS,
        COL_TEE,
        COL_SAND_OB,

        COL_MAX
    };

public:
    static void CreateInstance();
    static void DestroyInstance();

private:
    RPGlfCollisionModel();
    virtual ~RPGlfCollisionModel();
};

#endif
