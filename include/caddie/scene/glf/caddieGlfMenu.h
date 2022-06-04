#ifndef CADDIE_SCENE_GLF_MENU_H
#define CADDIE_SCENE_GLF_MENU_H
#include "caddieGlfMessage.h"
#include "caddieMenuBase.h"
#include "caddieMenuOption.h"
#include "caddieMenuPage.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Golf scene menu
 */
class GlfMenu : public MenuBase {
  public:
    GlfMenu();
    virtual ~GlfMenu();
    virtual void OnChange();

    static void Action_ApplyRestart(void* menu);
    static void Action_QuitGame(void* menu);

    int GetHole() const { return mHole.GetSavedValue(); }
    int GetHoleInternal() const { return GetHole() - 1; }
    bool GetRepeatHole() const { return mRepeatHole.GetSavedValue(); }
    int GetPinType() const { return mPinType.GetSavedValue(); }
    EWindDir GetWindDir() const { return (EWindDir)mWindDir.GetSavedValue(); }
    int GetWindSpd() const { return mWindSpd.GetSavedValue(); }
    EWindSpdRange GetWindSpdRange() const {
        return (EWindSpdRange)mWindSpdRange.GetSavedValue();
    }

  private:
    MenuIntOption mHole;
    MenuBoolOption mRepeatHole;
    MenuEnumOption mPinType;
    MenuEnumOption mWindDir;
    MenuEnumOption mWindSpd;
    MenuEnumOption mWindSpdRange;
    MenuActionOption mApplyRestart;
    MenuActionOption mQuitGame;

    //! @brief Menu X screen position
    static const f32 sMenuPosX;
    //! @brief Menu Y screen position
    static const f32 sMenuPosY;
};

} // namespace caddie

#endif
