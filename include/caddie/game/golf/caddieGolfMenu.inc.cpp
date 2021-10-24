#include "caddieGolfMenu.h"
#include "caddieLocalizer.h"

namespace caddie
{
    /* Wind Direction setting */

    static const char *sWindDirectionEnum[] =
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

    /* Wind Speed setting */

    static const char *sWindSpeedNames[Localizer::REGION_MAX] = 
    {
        "Wind Speed (mph)",
        "Wind Speed (m/s)",
        "Wind Speed (m/s)",
        "Wind Speed (m/s)",
    };

    static const char *sWindSpeedEnum_Mph[] =
    {
        "0", "2", "4", "6", "8", "10", "12", "14", "16", "18",
        "20", "22", "24", "26", "28", "30", "Random"
    };

    static const char *sWindSpeedEnum_Meters[] =
    {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "10", "11", "12", "13", "14", "15", "Random"
    };

    static const char **sWindSpeedLocale[Localizer::REGION_MAX] =
    {
        sWindSpeedEnum_Mph,
        sWindSpeedEnum_Meters,
        sWindSpeedEnum_Meters,
        sWindSpeedEnum_Meters
    };

    /* Random Wind Speed Range setting */

    static const char *sWindSpdRangeNames[Localizer::REGION_MAX] =
    {
        "Wind Speed Range",
        "Wind Speed Range",
        "Wind Speed Range",
        "Wind Speed Range"
    };

    static const char *sWindSpdRangeEnum_Mph[] =
    {
        "0-20 mph",
        "0-10 mph",
        "10-20 mph",
        "20-30 mph",
        "0-30 mph"
    };

    static const char *sWindSpdRangeEnum_Meters[] =
    {
        "0-20 m/s",
        "0-10 m/s",
        "10-20 m/s",
        "20-30 m/s",
        "0-30 m/s"
    };

    static const char **sWindSpdRangeLocale[Localizer::REGION_MAX] =
    {
        sWindSpdRangeEnum_Mph,
        sWindSpdRangeEnum_Meters,
        sWindSpdRangeEnum_Meters,
        sWindSpdRangeEnum_Meters
    };

    /* Pin Type setting */
    
    static const char *sPinTypeEnum[] =
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
    static const char *sPinTypeSpecialEnum[] =
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