#ifndef CADDIE_UI_MENU_PAGE_H
#define CADDIE_UI_MENU_PAGE_H
#include "caddieMenuOption.h"
#include "caddiePane.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Page of menu options
 */
class MenuPage : public Pane {
public:
    static u32 GetNodeOffset() { return offsetof(MenuPage, mNode); }

    MenuPage(const char* name, f32 x, f32 y, f32 leading = sDefaultLeading);
    virtual ~MenuPage();

    virtual void DrawSelf() const;

    void CalcWidth();

    f32 GetWidth() const { return mWidth; }
    void SetWidth(f32 w) { mWidth = w; }

    MenuPage* GetParentPage() const { return mParentPage; }
    void SetParentPage(MenuPage* p) { mParentPage = p; }

    bool IsRootPage() const { return (GetParentPage() == NULL); }

    void AppendChildPage(MenuPage* p) {
        CADDIE_ASSERT(p != NULL);
        mChildPages.Append(p);
        p->SetParentPage(this);
    }

    void AppendOption(IMenuOption* opt) {
        CADDIE_ASSERT(opt != NULL);
        mOptions.Append(opt);
        CalcWidth();
    }

    IMenuOption& GetOption(int i) const {
        CADDIE_ASSERT(i < GetNumOptions());
        return *mOptions.At(i);
    }

    u32 GetNumOptions() const { return mOptions.Size(); }

    void SaveChanges();
    void DeleteChanges();

private:
    //! @brief Node for intrusive list
    TLinkListNode mNode;

private:
    //! @brief Parent page
    MenuPage* mParentPage;
    //! @brief Child pages
    TLinkList<MenuPage> mChildPages;
    //! @brief Page options
    TLinkList<IMenuOption> mOptions;
    //! @brief Page leading
    f32 mLeading;
    //! @brief Page width
    f32 mWidth;

    static const f32 sDefaultLeading;
    static const f32 sCharWidth;
};

} // namespace caddie

#endif
