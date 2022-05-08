#include "caddieMenuMgr.h"

namespace caddie
{
    /**
     * @brief Menu logic
     */
    void MenuMgr::Calc()
    {

    }

    /**
     * @brief Draw focused page
     */
    void MenuMgr::Draw() const
    {
        mPageStack.Peek()->Draw();
    }
}