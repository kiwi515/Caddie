#ifndef CADDIE_UI_MENU_BASE_H
#define CADDIE_UI_MENU_BASE_H
#include "types_caddie.h"
#include "caddieMenuPage.h"

namespace caddie
{
    /**
     * @brief Base menu class used by the menu manager
     */
    class MenuBase
    {
    public:
        MenuBase(const char* rootName, f32 x, f32 y) :
            mIsAwaitingApply(false),
            mCanDelete(false),
            mRootPage(rootName, x, y)
        {
        }

        virtual ~MenuBase()
        {
        }

        void SaveChanges() { mRootPage.SaveChanges(); }
        void DeleteChanges() { mRootPage.DeleteChanges(); }

        bool IsAwaitingApply() const { return mIsAwaitingApply; }
        void SetAwaitingApply(bool save) { mIsAwaitingApply = save; }

        bool CanDelete() const { return mCanDelete; }
        void SetCanDelete(bool del) { mCanDelete = del; }

        MenuPage& GetRootPage() { return mRootPage; }
        const MenuPage& GetRootPage() const { return mRootPage; }

    private:
        //! @brief Settings are waiting to be applied
        bool mIsAwaitingApply;
        //! @brief Prevent menu from being deleted on scene re-init
        bool mCanDelete;
        //! @brief Menu root
        MenuPage mRootPage;
    };
}

#endif