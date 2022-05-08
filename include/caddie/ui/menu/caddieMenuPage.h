#ifndef CADDIE_UI_MENU_PAGE_H
#define CADDIE_UI_MENU_PAGE_H
#include "types_caddie.h"
#include "caddiePane.h"

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

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;
    };

    typedef TLinkList<MenuPage, offsetof(MenuPage, mNode)> MenuPageList;
    typedef MenuPageList::Iterator MenuPageIterator;
}

#endif