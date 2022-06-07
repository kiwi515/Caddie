#ifndef CADDIE_UI_MENU_MGR_H
#define CADDIE_UI_MENU_MGR_H
#include "caddieMenuBase.h"
#include "caddieMenuPage.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Menu context manager
 */
class MenuMgr {
  public:
    static MenuMgr& GetInstance() {
        static MenuMgr instance;
        return instance;
    }

    virtual void Calc();
    virtual void Draw() const;

    void OpenMenu(MenuBase* menu) {
        CADDIE_ASSERT(menu != NULL);
        mMenu = menu;
        mOpenPage = &menu->GetRootPage();
        mCursor = 0;
        mMenu->OnChange();
    }

    void ClosePage() {
        if (!mOpenPage->IsRootPage()) {
            mOpenPage = mOpenPage->GetParentPage();
            mCursor = 0;
        }
    }

    int GetCursor() const { return mCursor; }
    void SetCursor(int cursor) { mCursor = cursor; }

    bool IsVisible() const { return mIsVisible; }
    void SetVisible(bool vis) { mIsVisible = vis; }

  private:
    MenuMgr()
        : mMenu(NULL),
          mOpenPage(NULL),
          mCursor(0),
          mIsVisible(false),
          mBtnHeld(0x0),
          mBtnTrig(0x0),
          mBtnReleased(0x0) {
        // Set up cursor textbox
        mCursorText.SetText(sCursorStr);
        mCursorText.SetTextColor(sCursorColor);
        mCursorText.SetStroke(TextBox::STROKE_OUTLINE);
    }
    virtual ~MenuMgr() {}

    void CalcInput();

  private:
    //! @brief Current menu
    MenuBase* mMenu;
    //! @brief Current page
    MenuPage* mOpenPage;
    //! @brief Cursor position
    int mCursor;
    //! @brief Cursor textbox
    TextBox mCursorText;
    //! @brief Visiblity flag
    bool mIsVisible;

    //! @brief Buttons being held
    u32 mBtnHeld;
    //! @brief Buttons pressed this frame
    u32 mBtnTrig;
    //! @brief Buttons released
    u32 mBtnReleased;

    //! @brief Delayed auto shift
    s32 mControlDAS;
    //! @brief Auto repeat rate
    s32 mControlARR;

    //! @brief Menu delay before auto repeat (in frames)
    static const u32 sControlMaxDAS;
    //! @brief Menu auto repeat rate (in frames)
    static const u32 sControlMaxARR;

    //! @brief Cursor text string
    static const char* sCursorStr;
    //! @brief Cursor text color
    static const nw4r::ut::Color sCursorColor;
    //! @brief Cursor text X offset from option
    static const f32 sCursorOffset;
};

} // namespace caddie

#endif
