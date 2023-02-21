#include "caddieGlfUtil.h"

#include <Sports2/Scene/Glf/Sp2GlfMain.h>

namespace caddie {

/**
 * @brief Whether the current hole is the first hole of the gamemode
 */
bool GlfUtil::IsCurrentFirstHole() {
    Sp2::Glf::GlfMain& main = Sp2::Glf::GlfMain::getInstance();
    return IsFirstHoleInternal(main.getGamemode(), main.getCurrentHole());
}

/**
 * @brief Whether the specified hole is the first hole of the gamemode
 * @note Hole is zero-indexed
 * @param gm Gamemode
 * @param hole Hole (zero-indexed)
 */
bool GlfUtil::IsFirstHoleInternal(Sp2::Glf::GameMode gm, u32 hole) {
    return IsFirstHole(gm, hole + 1);
}

/**
 * @brief Whether the specified hole is the first hole of the gamemode
 * @note Hole is one-indexed
 * @param gm Gamemode
 * @param hole Hole (one-indexed)
 */
bool GlfUtil::IsFirstHole(Sp2::Glf::GameMode gm, u32 hole) {
    switch (gm) {
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
bool GlfUtil::IsCurrentRoundOver() {
    Sp2::Glf::GlfMain& main = Sp2::Glf::GlfMain::getInstance();
    return IsRoundOverInternal(main.getGamemode(), main.getCurrentHole());
}

/**
 * @brief Whether the round will be over at the next hole (hole is past end of
 * difficulty)
 */
bool GlfUtil::IsNextRoundOver() {
    Sp2::Glf::GlfMain& main = Sp2::Glf::GlfMain::getInstance();
    return IsRoundOverInternal(main.getGamemode(), main.getCurrentHole() + 1);
}

/**
 * @brief Whether the round is over (hole is past end of difficulty)
 * @note Hole is zero-indexed
 * @param gm Gamemode
 * @param hole Hole (zero-indexed)
 */
bool GlfUtil::IsRoundOverInternal(Sp2::Glf::GameMode gm, u32 hole) {
    return IsRoundOver(gm, hole + 1);
}

/**
 * @brief Whether the round is over (hole is past end of difficulty)
 * @note Hole is one-indexed
 * @param gm Gamemode
 * @param hole Hole (one-indexed)
 */
bool GlfUtil::IsRoundOver(Sp2::Glf::GameMode gm, u32 hole) {
    switch (gm) {
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

/**
 * @brief Calculate the nth hole of the current gamemode
 * @details Hole is zero-indexed (internal)
 */
u32 GlfUtil::GetGamemodeNthHoleInternal(u32 n) {
    return GetGamemodeNthHole(n) - 1;
}

/**
 * @brief Calculate the nth hole of the current gamemode
 * @details Hole is one-indexed
 */
u32 GlfUtil::GetGamemodeNthHole(u32 n) {
    switch (Sp2::Glf::GlfMain::getInstance().getGamemode()) {
    case Sp2::Glf::GM_EIGHTEEN_HOLE:
    case Sp2::Glf::GM_RESORT_NINE:
    case Sp2::Glf::GM_RESORT_A:
        return 1 + n;
    case Sp2::Glf::GM_RESORT_B:
        return 4 + n;
    case Sp2::Glf::GM_RESORT_C:
        return 7 + n;
    case Sp2::Glf::GM_CLASSIC_NINE:
    case Sp2::Glf::GM_CLASSIC_A:
        return 10 + n;
    case Sp2::Glf::GM_CLASSIC_B:
        return 13 + n;
    case Sp2::Glf::GM_CLASSIC_C:
        return 16 + n;
    case Sp2::Glf::GM_SPECIAL:
        return 19 + n;
    }
}

} // namespace caddie
