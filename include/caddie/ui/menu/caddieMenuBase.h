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
            mIsAwaitingSave(false),
            mRootPage(rootName, x, y)
        {
        }

        virtual ~MenuBase()
        {
        }

        void SaveChanges() { mRootPage.SaveChanges(); }
        void DeleteChanges() { mRootPage.DeleteChanges(); }

        bool IsAwaitingSave() const { return mIsAwaitingSave; }
        void SetAwaitingSave(bool save) { mIsAwaitingSave = save; }

        MenuPage& GetRootPage() { return mRootPage; }
        const MenuPage& GetRootPage() const { return mRootPage; }

    private:
        //! @brief Prevents menu from being deleted on scene exit
        bool mIsAwaitingSave;
        //! @brief Menu root
        MenuPage mRootPage;
    };
}

#endif