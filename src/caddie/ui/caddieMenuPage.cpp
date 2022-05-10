#include "caddieMenuPage.h"

using namespace nw4r::math;

namespace caddie
{
    MenuPage::MenuPage(const char* name, f32 x, f32 y, f32 width, f32 leading) :
        mWidth(width),
        mLeading(leading)
    {
        SetName(name);
        SetPosition(VEC2(x, y));
    }

    MenuPage::~MenuPage()
    {
        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            delete &*it;
        }
    }

    /**
     * @brief Draw all options on page
     */
    void MenuPage::DrawSelf() const
    {       
        VEC2 namePos = mPos;

        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++) {
            it->SetNamePosition(namePos);
            
            VEC2 valuePos = namePos;
            valuePos.mCoords.x += mWidth;
            it->SetValuePosition(valuePos);

            it->Draw();

            namePos.mCoords.y += mLeading;
        }
    }

    /**
     * @brief Get option by name
     * 
     * @param name Option name
     */
    IMenuOption* MenuPage::GetOption(const char* name) const
    {
        MenuOptionIterator it = mOptions.Begin();
        for (; it != mOptions.End(); it++) {
            if (strcmp(name, it->GetName()) == 0) {
                return &*it;
            }
        }

        return NULL;
    }
}