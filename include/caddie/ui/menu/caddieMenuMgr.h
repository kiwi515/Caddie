#ifndef CADDIE_UI_MENU_MGR_H
#define CADDIE_UI_MENU_MGR_H
#include "caddieInputMgr.h"
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

    MenuBase* GetMenu() const { return mMenu; }

    void OpenMenu(MenuBase* menu) {
        CADDIE_ASSERT(menu != NULL);
        mMenu = menu;
        mOpenPage = &menu->GetRootPage();
        mCursor = 0;
        mMenu->OnChange();
    }

    void OpenPage(MenuPage* page) {
        CADDIE_ASSERT(page != NULL);
        CADDIE_ASSERT_EX(page->GetParentPage() == mOpenPage,
                         "Orphan menu page?");
        mOpenPage = page;
        mCursor = 0;
    }

    void CloseMenu() {
        if (mMenu != NULL && mOpenPage != NULL) {
            mMenu->DeleteChanges();
            mMenu = NULL;
            mOpenPage = NULL;
        }
    }

    void ClosePage() {
        if (mOpenPage != NULL && !mOpenPage->IsRootPage()) {
            mOpenPage = mOpenPage->GetParentPage();
            mCursor = 0;
        }
    }

    int GetCursor() const { return mCursor; }
    void SetCursor(int cursor) { mCursor = cursor; }

    bool IsVisible() const { return mIsVisible; }
    void SetVisible(bool vis) { mIsVisible = vis; }

private:
    MenuMgr() : mMenu(NULL), mOpenPage(NULL), mCursor(0), mIsVisible(false) {
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

    //! @brief Delayed auto shift
    s32 mControlDAS[InputMgr::PLAYER_MAX];
    //! @brief Auto repeat rate
    s32 mControlARR[InputMgr::PLAYER_MAX];

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
