#ifndef CADDIE_UI_MENU_MGR_H
#define CADDIE_UI_MENU_MGR_H
#include "types_caddie.h"
#include "caddieMenuPage.h"
#include "caddieStack.h"

namespace caddie
{
    /**
     * @brief Menu context manager
     */
    class MenuMgr
    {
    public:
        static MenuMgr& GetInstance()
        {
            static MenuMgr instance;
            return instance;
        }

        virtual void Calc();
        virtual void Draw() const;

        void OpenPage(MenuPage* page)
        {
            CADDIE_ASSERT(page != NULL);
            mPageStack.Push(page);
            mCursor = 0;
        }

        void ClosePage()
        {
            mPageStack.Pop();
            mCursor = 0;
        }

        int GetCursor() const { return mCursor; }
        void SetCursor(int cursor) { mCursor = cursor; }

        bool IsVisible() const { return mIsVisible; }
        void SetVisible(bool vis) { mIsVisible = vis; }

    private:
        MenuMgr() :
            mCursor(0),
            mIsVisible(false),
            mBtnHeld(0x0),
            mBtnTrig(0x0),
            mBtnReleased(0x0)
        {
            // Set up cursor textbox
            mCursorText.SetText(sCursorStr);
            mCursorText.SetTextColor(sCursorColor);
            mCursorText.SetStroke(TextBox::STROKE_OUTLINE);
        }

        virtual ~MenuMgr()
        {
        }

        void CalcInput();

    private:
        //! @brief Menu page hierarchy
        TStack<MenuPage> mPageStack;
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

        static const char* sCursorStr;
        static const nw4r::ut::Color sCursorColor;
        static const f32 sCursorOffset;
    };
}

#endif