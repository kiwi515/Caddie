#ifndef CADDIE_SCENE_GLF_POST_MENU_H
#define CADDIE_SCENE_GLF_POST_MENU_H
#include "caddieGlfMessage.h"
#include "caddieMenuBase.h"
#include "caddieMenuOption.h"
#include "caddieMenuPage.h"
#include "types_caddie.h"

namespace caddie {

class GlfPostMenu : public MenuBase {
public:
    GlfPostMenu();
    virtual ~GlfPostMenu();
    virtual void OnChange() {}

    static void Action_NextShot(void* menu);
    static void Action_TryAgain(void* menu);

    static void ChangePhase();

private:
    MenuActionOption mNextShot;
    MenuActionOption mTryAgain;

    //! @brief Menu X screen position
    static const f32 sMenuPosX;
    //! @brief Menu Y screen position
    static const f32 sMenuPosY;
};

} // namespace caddie

#endif
