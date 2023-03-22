#ifndef CADDIE_EXTENSION_SCENE_CREATOR_H
#define CADDIE_EXTENSION_SCENE_CREATOR_H
#include "types_caddie.hpp"

#include <RPSysSceneCreator.h>

namespace caddie {

/**
 * @brief Caddie extension to WS2 scene creator
 */
class SceneCreatorEx : public RPSysSceneCreator {
public:
    static SceneCreatorEx& GetInstance() {
        return static_cast<SceneCreatorEx&>(RPSysSceneCreator::getInstance());
    }

    RPSysScene* CreateEx(ESceneID id);
    ESceneID GetTitleScene() const;

private:
    RPSysScene* CreateCaddieScene(ESceneID id);

    SceneCreatorEx() { CADDIE_ASSERT(false); }
    SceneCreatorEx(const SceneCreatorEx&) { CADDIE_ASSERT(false); }
    ~SceneCreatorEx() { CADDIE_ASSERT(false); }
};

// Data should not be added to this class to ensure compatability
CADDIE_STATIC_ASSERT(sizeof(SceneCreatorEx) == sizeof(RPSysSceneCreator));

} // namespace caddie

#endif
