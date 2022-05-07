#ifndef CADDIE_UI_MENU_H
#define CADDIE_UI_MENU_H
#include "types_caddie.h"
#include "caddieMenuPage.h"

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

        MenuPage* GetMenuPages() const { return mMenuPages; }
        void SetMenuPages(MenuPage* pages) { mMenuPages = pages; }

        int GetPage() const { return mPage; }
        void SetPage(int page) { mPage = page; }

        int GetCursor() const { return mCursor; }
        void SetCursor(int cursor) { mCursor = cursor; }

        bool GetVisible() const { return mIsVisible; }
        void SetVisible(bool vis) { mIsVisible = vis; }

        void NextPage() { mPage = (mPage + 1) % mNumPages; }
        void PrevPage() { mPage = (mPage == 0) ? mNumPages : (mPage - 1) % mNumPages; }

    private:
        MenuMgr() :
            mMenuPages(NULL),
            mNumPages(0),
            mPage(0),
            mCursor(0),
            mIsVisible(false)
        {}
        virtual ~MenuMgr() {}

    private:
        //! @brief Menu data
        MenuPage* mMenuPages;
        //! @brief Page count
        int mNumPages;
        //! @brief Current page
        int mPage;
        //! @brief Cursor position
        int mCursor;
        //! @brief Visiblity flag
        bool mIsVisible;
    };
}

#endif