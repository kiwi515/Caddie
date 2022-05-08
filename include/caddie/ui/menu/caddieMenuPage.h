#ifndef CADDIE_UI_MENU_PAGE_H
#define CADDIE_UI_MENU_PAGE_H
#include "types_caddie.h"
#include "caddiePane.h"
#include "caddieMenuOption.h"
#include "caddieAssert.h"

namespace caddie
{
    /**
     * @brief Page of menu options
     */
    class MenuPage : public Pane
    {
    public:
        MenuPage() {}
        virtual ~MenuPage() {}

        virtual void Draw() const;

        f32 GetWidth() const { return mWidth; }
        void SetWidth(f32 w) { mWidth = w; }

        void AppendOption(IMenuOption *opt)
        {
            CADDIE_ASSERT(opt != NULL);
            mOptions.Append(opt);
        }

        IMenuOption* GetOption(int i) const
        {
            return mOptions.At(i);
        }

        IMenuOption* GetOption(const char *name) const;

        u32 GetNumOptions() const { return mOptions.Size(); }

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    private:
        //! @brief Page options
        MenuOptionList mOptions;
        //! @brief Page leading
        f32 mLeading;
        //! @brief Page width
        f32 mWidth;
    };

    typedef TLinkList<MenuPage, offsetof(MenuPage, mNode)> MenuPageList;
    typedef MenuPageList::Iterator MenuPageIterator;
}

#endif