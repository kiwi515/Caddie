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

        void AppendOption(IMenuOption *opt)
        {
            CADDIE_ASSERT(opt != NULL);
            mOptions.Append(opt);
        }

        IMenuOption* GetOption(int i) const
        {
            return mOptions.At(i);
        }

        IMenuOption* GetOption(const char *name) const
        {
            MenuOptionIterator it = mChildren.Begin();
            for (; it != mChildren.End(); it++) {
                if (strcmp(name, it->GetName()) == 0) {
                    return &*it;
                }
            }

            return NULL;
        }

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    private:
        //! @brief Page options
        MenuOptionList mOptions;
    };

    typedef TLinkList<MenuPage, offsetof(MenuPage, mNode)> MenuPageList;
    typedef MenuPageList::Iterator MenuPageIterator;
}

#endif