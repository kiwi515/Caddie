#include "caddieGlfMessage.h"

using namespace Sp2;

namespace caddie
{
    //! @brief Text for menu title
    const char* MSG_MENU_TITLE = "Golf Menu";

    //! @brief Text for Hole option
    const char* MSG_HOLE = "Hole";

    //! @brief Text for Repeat Hole option
    const char* MSG_REPEAT_HOLE = "Repeat Hole";

    //! @brief Text for Pin Type option
    const char* MSG_PIN_TYPE = "Pin Type";

    //! @brief Text for Wind Direction option
    const char* MSG_WIND_DIR = "Wind Direction";

    //! @brief Text for Wind Speed option
    const char* MSG_WIND_SPD = CADDIE_LOCALIZE(
        "Wind Speed (mph)",
        "Wind Speed (m/s)",
        "Wind Speed (m/s)",
        "Wind Speed (m/s)"
    );

    //! @brief Text for Wind Speed Range option
    const char* MSG_WIND_SPD_RANGE = "Wind Speed Range";

    //! @brief Text for Apply and Restart option
    const char* MSG_APPLY = "Apply and Restart";

    //! @brief Text for Quit Game option
    const char* MSG_QUIT = "Quit Game";

    //! @brief String binding of pin type enum
    const char* ENUM_PIN_TYPE[PIN_MAX] = {
        "Pin 1 (B)",
        "Pin 2 (B)",
        "Pin 3 (B)",
        "Pin 4 (A)",
        "Pin 5 (A)",
        "Pin 6 (A)",
        "From Score",
        "Random (All)",
        "Random (A)",
        "Random (B)"
    };

    //! @brief String binding of Hole 1 pin type enum
    const char* ENUM_PIN_TYPE_HOLE1[H1_PIN_MAX] = {
        "Pin 1",
        "Pin 2",
        "Pin 3",
        "Random (All)",
    };

    //! @brief String binding of Special pin type enum
    const char* ENUM_PIN_TYPE_SPECIAL[SP_PIN_MAX] = {
        "Pin 1",
        "Pin 2",
        "Pin 3",
        "Pin 4",
        "Pin 5",
        "Pin 6",
        "Random (All)"
    };

    //! @brief String binding of wind direction enum
    const char* ENUM_WIND_DIR[DIR_MAX] = {
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

    //! @brief String binding of wind speed enum
    const char* ENUM_WIND_SPD[] = {
        "0",
        CADDIE_LOCALIZE("2",  "1",  "1",  "1"),
        CADDIE_LOCALIZE("4",  "2",  "2",  "2"),
        CADDIE_LOCALIZE("6",  "3",  "3",  "3"),
        CADDIE_LOCALIZE("8",  "4",  "4",  "4"),
        CADDIE_LOCALIZE("10", "5",  "5",  "5"),
        CADDIE_LOCALIZE("12", "6",  "6",  "6"),
        CADDIE_LOCALIZE("14", "7",  "7",  "7"),
        CADDIE_LOCALIZE("16", "8",  "8",  "8"),
        CADDIE_LOCALIZE("18", "9",  "9",  "9"),
        CADDIE_LOCALIZE("20", "10", "10", "10"),
        CADDIE_LOCALIZE("22", "11", "11", "11"),
        CADDIE_LOCALIZE("24", "12", "12", "12"),
        CADDIE_LOCALIZE("26", "13", "13", "13"),
        CADDIE_LOCALIZE("28", "14", "14", "14"),
        CADDIE_LOCALIZE("30", "15", "15", "15"),
        "Random"
    };

    //! @brief String binding of wind speed range enum
    const char* ENUM_WIND_SPD_RANGE[RANGE_MAX] = {
        CADDIE_LOCALIZE("0-20 mph",  "0-10 m/s",  "0-10 m/s",  "0-10 m/s"),
        CADDIE_LOCALIZE("0-10 mph",  "0-5 m/s",   "0-5 m/s",   "0-5 m/s"),
        CADDIE_LOCALIZE("10-20 mph", "5-10 m/s",  "5-10 m/s",  "5-10 m/s"),
        CADDIE_LOCALIZE("20-30 mph", "10-15 m/s", "10-15 m/s", "10-15 m/s"),
        CADDIE_LOCALIZE("0-30 mph",  "0-15 m/s",  "0-15 m/s",  "0-15 m/s")
    };
}