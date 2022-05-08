#include "caddieMenuPage.h"

using namespace nw4r::math;

namespace caddie
{
    /**
     * @brief Draw all options on page
     */
    void MenuPage::Draw() const
    {
        VEC2 namePos = mPos;

        MenuOptionIterator it = mOptions.Begin();
        for(; it != mOptions.End(); it++)
        {
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