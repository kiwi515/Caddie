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

        bool GetVisible() const { return mIsVisible; }
        void SetVisible(bool vis) { mIsVisible = vis; }

    private:
        MenuMgr() :
            mCursor(0),
            mIsVisible(false)
        {}
        virtual ~MenuMgr() {}

    private:
        //! @brief Menu page hierarchy
        Stack<MenuPage> mPageStack;
        //! @brief Cursor position
        u32 mCursor;
        //! @brief Visiblity flag
        bool mIsVisible;
    };
}

#endif