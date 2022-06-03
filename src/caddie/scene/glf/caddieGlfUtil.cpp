#include "caddieGlfUtil.h"
#include "caddieAssert.h"

#include <Sports2/Scene/Glf/Sp2GlfMain.h>

namespace caddie
{
    /**
     * @brief Whether the current hole is the first hole of the gamemode
     */
    bool GlfUtil::IsCurrentFirstHole()
    {
        Sp2::Glf::GlfMain* main = Sp2::Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        return IsFirstHole(main->getGamemode(), main->getCurrentHole());
    }

    /**
     * @brief Whether the specified hole is the first hole of the gamemode
     * @note Hole is zero-indexed
     * @param gm Gamemode
     * @param hole Hole (zero-indexed)
     */
    bool GlfUtil::IsFirstHole(Sp2::Glf::GameMode gm, u32 hole)
    {
        return IsFirstHoleInternal(gm, hole + 1);
    }

    /**
     * @brief Whether the specified hole is the first hole of the gamemode
     * @note Hole is one-indexed
     * @param gm Gamemode
     * @param hole Hole (one-indexed)
     */
    bool GlfUtil::IsFirstHoleInternal(Sp2::Glf::GameMode gm, u32 hole)
    {
        switch(gm)
        {
            case Sp2::Glf::GM_EIGHTEEN_HOLE:
            case Sp2::Glf::GM_RESORT_NINE:
            case Sp2::Glf::GM_RESORT_A:
                return hole == 1;
            case Sp2::Glf::GM_CLASSIC_NINE:
            case Sp2::Glf::GM_CLASSIC_A:
                return hole == 10;
            case Sp2::Glf::GM_RESORT_B:
                return hole == 4;
            case Sp2::Glf::GM_RESORT_C:
                return hole == 7;
            case Sp2::Glf::GM_CLASSIC_B:
                return hole == 13;
            case Sp2::Glf::GM_CLASSIC_C:
                return hole == 16;
            case Sp2::Glf::GM_SPECIAL:
                return hole == 19;
            default:
                CADDIE_ASSERT(false);
                return false;
        }
    }

    /**
     * @brief Whether the current round is over (hole is past end of difficulty)
     */
    bool GlfUtil::IsCurrentRoundOver()
    {
        Sp2::Glf::GlfMain* main = Sp2::Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        return IsRoundOver(main->getGamemode(), main->getCurrentHole());
    }

    /**
     * @brief Whether the round will be over at the next hole (hole is past end of difficulty)
     */
    bool GlfUtil::IsNextRoundOver()
    {
        Sp2::Glf::GlfMain* main = Sp2::Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        return IsRoundOver(main->getGamemode(), main->getCurrentHole() + 1);
    }

    /**
     * @brief Whether the round is over (hole is past end of difficulty)
     * @note Hole is zero-indexed
     * @param gm Gamemode
     * @param hole Hole (zero-indexed)
     */
    bool GlfUtil::IsRoundOver(Sp2::Glf::GameMode gm, u32 hole)
    {
        return IsRoundOverInternal(gm, hole + 1);
    }

    /**
     * @brief Whether the round is over (hole is past end of difficulty)
     * @note Hole is one-indexed
     * @param gm Gamemode
     * @param hole Hole (one-indexed)
     */
    bool GlfUtil::IsRoundOverInternal(Sp2::Glf::GameMode gm, u32 hole)
    {
        switch(gm)
        {
            case Sp2::Glf::GM_EIGHTEEN_HOLE:
            case Sp2::Glf::GM_CLASSIC_NINE:
            case Sp2::Glf::GM_CLASSIC_C:
                return hole > 18;
            case Sp2::Glf::GM_RESORT_NINE:
            case Sp2::Glf::GM_RESORT_C:
                return hole > 9;
            case Sp2::Glf::GM_RESORT_A:
                return hole > 3;
            case Sp2::Glf::GM_CLASSIC_A:
                return hole > 12;
            case Sp2::Glf::GM_RESORT_B:
                return hole > 6;
            case Sp2::Glf::GM_CLASSIC_B:
                return hole > 15;
            case Sp2::Glf::GM_SPECIAL:
                return hole > 21;
            default:
                CADDIE_ASSERT(false);
                return true;
        }
    }
}