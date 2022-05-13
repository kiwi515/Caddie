#include "caddieMenuPage.h"

using namespace nw4r;

namespace caddie
{
    /**
     * @note Width is dynamically calculated later
     */
    MenuPage::MenuPage(const char* name, f32 x, f32 y, f32 leading) :
        mLeading(leading),
        mWidth(0.0f)
    {
        SetName(name);
        SetPosition(math::VEC2(x, y));
    }

    MenuPage::~MenuPage()
    {
        // TODO: Fix this

        // MenuOptionIterator it = mOptions.Begin();
        // for(; it != mOptions.End(); it++) {
        //     MenuOptionIterator next = it++;
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

        MenuOptionIterator it = mOptions.Begin();
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

        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            const size_t nameLen = strlen(it->GetName());
            max = MAX(nameLen, max);
        }

        mWidth = max * sCharWidth;
    }

    /**
     * @brief Save all options' changes
     */
    void MenuPage::SaveChanges()
    {
        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            it->SaveChanges();
        }   
    }

    /**
     * @brief Delete all options' changes
     */
    void MenuPage::DeleteChanges()
    {
        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            it->DeleteChanges();
        }   
    }

    //! @brief Default option leading
    const f32 MenuPage::sDefaultLeading = 20.0f;
    //! @brief Estimated text character width
    const f32 MenuPage::sCharWidth = 9.0f;
}