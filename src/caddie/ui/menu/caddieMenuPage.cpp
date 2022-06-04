#include "caddieMenuPage.h"
#include "caddieAlgorithm.h"

using namespace nw4r;

namespace caddie
{
    /**
     * @note Width is dynamically calculated later
     */
    MenuPage::MenuPage(const char* name, f32 x, f32 y, f32 leading) :
        mParentPage(NULL),
        mLeading(leading),
        mWidth(0.0f)
    {
        SetName(name);
        SetPosition(math::VEC2(x, y));
    }

    MenuPage::~MenuPage()
    {
        // TODO: Fix this

        // TLinkList<IMenuOption>::Iterator it = mOptions.Begin();
        // for(; it != mOptions.End(); it++) {
        //     TLinkList<IMenuOption>::Iterator next = it++;
        //     mOptions.Remove(next);
        //     delete &*next;
        // }
    }

    /**
     * @brief Draw all options on page
     */
    void MenuPage::DrawSelf() const
    {
        math::VEC2 pos = mPos;

        TLinkList<IMenuOption>::Iterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            it->SetOptionPosition(pos, mWidth);
            it->Draw();
            pos.mCoords.y += mLeading;
        }
    }

    /**
     * @brief Calculate menu option width,
     * based on the longest option name
     */
    void MenuPage::CalcWidth()
    {
        size_t max = 0;

        TLinkList<IMenuOption>::Iterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            const size_t nameLen = strlen(it->GetName());
            max = Max(nameLen, max);
        }

        mWidth = max * sCharWidth;
    }

    /**
     * @brief Save all options' changes
     */
    void MenuPage::SaveChanges()
    {
        // Save changes in this page
        TLinkList<IMenuOption>::Iterator option = mOptions.Begin();
        for(; option != mOptions.End(); option++) {
            option->SaveChanges();
        }

        // Save changes in children
        TLinkList<MenuPage>::Iterator page = mChildPages.Begin();
        for (; page != mChildPages.End(); page++) {
            page->SaveChanges();
        }
    }

    /**
     * @brief Delete all options' changes
     */
    void MenuPage::DeleteChanges()
    {
        // Delete changes in this page
        TLinkList<IMenuOption>::Iterator option = mOptions.Begin();
        for(; option != mOptions.End(); option++) {
            option->DeleteChanges();
        }

        // Delete changes in children
        TLinkList<MenuPage>::Iterator page = mChildPages.Begin();
        for (; page != mChildPages.End(); page++) {
            page->DeleteChanges();
        }
    }

    //! @brief Default option leading
    const f32 MenuPage::sDefaultLeading = 20.0f;
    //! @brief Estimated text character width
    const f32 MenuPage::sCharWidth = 9.0f;
}
