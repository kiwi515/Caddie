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
        "Southwest",
        "Random"
    };

    const char *GolfMenu::sWindSpeeds[] =
    {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "10", "11", "12", "13", "14", "15", "Random"
    };

    const char *GolfMenu::sRandWindSpdRanges[] =
    {
        "0-20 mph",
        "0-10 mph",
        "10-20 mph",
        "20-30 mph",
        "0-30 mph"
    };

    const char *GolfMenu::sPinTypes[] =
    {
        "From Score",
        "Random",
        "Pin 1 (B)",
        "Pin 2 (B)",
        "Pin 3 (B)",
        "Pin 4 (A)",
        "Pin 5 (A)",
        "Pin 6 (A)"
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