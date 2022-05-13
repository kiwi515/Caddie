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

    const f32 MenuPage::sDefaultLeading = 20.0f;
    const f32 MenuPage::sCharWidth = 9.0f;
}