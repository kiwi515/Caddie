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
        static u32 GetNodeOffset() { return offsetof(MenuPage, mNode); }

        MenuPage(const char* name, f32 x, f32 y, f32 width = 10.0f, f32 leading = 5.0f);
        virtual ~MenuPage();

        virtual void DrawSelf() const;

        f32 GetWidth() const { return mWidth; }
        void SetWidth(f32 w) { mWidth = w; }

        void AppendOption(IMenuOption *opt)
        {
            CADDIE_ASSERT(opt != NULL);
            mOptions.Append(opt);
        }

        IMenuOption& GetOption(int i) const
        {
            CADDIE_ASSERT(i < GetNumOptions());
            return *mOptions.At(i);
        }

        IMenuOption* GetOption(const char* name) const;

        u32 GetNumOptions() const { return mOptions.Size(); }

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    private:
        //! @brief Page options
        TLinkList<IMenuOption> mOptions;
        //! @brief Page leading
        f32 mLeading;
        //! @brief Page width
        f32 mWidth;
    };

    typedef TLinkList<MenuPage> MenuPageList;
    typedef MenuPageList::Iterator MenuPageIterator;
}

#endif