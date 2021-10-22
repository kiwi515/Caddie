#include "caddieGolfMenu.h"

namespace caddie
{
    const char *GolfMenu::sWindDirections[] =
    {
        "South",
        "Southeast",
        "East",
        "Northeast",
        "North",
        "Northwest",
        "West",
        "Southwest"
    };

    const char *GolfMenu::sPinTypes[] =
    {
        "From Score",
        "Random",
        "Pin 1 (A)",
        "Pin 2 (A)",
        "Pin 3 (A)",
        "Pin 4 (B)",
        "Pin 5 (B)",
        "Pin 6 (B)"
    };

    // Used for holes that do not have pin sets by score (Hole 1, Hole 18, Holes 19-21)
    const char *GolfMenu::sSpecialPinTypes[] =
    {
        "From Score",
        "Random",
        "Pin 1",
        "Pin 2",
        "Pin 3",
        "Pin 4",
        "Pin 5",
        "Pin 6"
    };
}