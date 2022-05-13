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

        MenuPage(const char* name, f32 x, f32 y, f32 leading = sDefaultLeading);
        virtual ~MenuPage();

        virtual void DrawSelf() const;

        void CalcWidth();

        f32 GetWidth() const { return mWidth; }
        void SetWidth(f32 w) { mWidth = w; }

        void AppendOption(IMenuOption *opt)
        {
            CADDIE_ASSERT(opt != NULL);
            mOptions.Append(opt);
            CalcWidth();
        }

        IMenuOption& GetOption(int i) const
        {
            CADDIE_ASSERT(i < GetNumOptions());
            return *mOptions.At(i);
        }

        u32 GetNumOptions() const { return mOptions.Size(); }

        void SaveChanges();
        void DeleteChanges();

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

        static const f32 sDefaultLeading;
        static const f32 sCharWidth;
    };

    typedef TLinkList<MenuPage> MenuPageList;
    typedef MenuPageList::Iterator MenuPageIterator;
}

#endif