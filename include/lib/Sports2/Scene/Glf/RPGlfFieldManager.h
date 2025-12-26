#ifndef RP_SPORTS_GLF_FIELD_MANAGER_H
#define RP_SPORTS_GLF_FIELD_MANAGER_H
#include "types_RP.h"
#include "types_caddie.h"

#include <nw4r/math/math_types.h>

class RPGlfFieldManager {
public:
    static RPGlfFieldManager& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    const nw4r::math::VEC3& GetPinPos() const;
    bool IsHideUI() const;

private:
    static RPGlfFieldManager* sInstance;
};

#endif
