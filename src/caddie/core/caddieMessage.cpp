#include "caddieMessage.h"

/**
 * @brief Define a localizable message.
 * @note Evaluated at compile time
 */
#ifdef CADDIE_REGION_NTSC_U
    #define MESSAGE_DEF(NTSC_U, PAL, NTSC_J, KOR) NTSC_U
#elif CADDIE_REGION_PAL
    #define MESSAGE_DEF(NTSC_U, PAL, NTSC_J, KOR) PAL
#elif CADDIE_REGION_NTSC_J
    #define MESSAGE_DEF(NTSC_U, PAL, NTSC_J, KOR) NTSC_J
#elif CADDIE_REGION_KOR
    #define MESSAGE_DEF(NTSC_U, PAL, NTSC_J, KOR) KOR
#else
    #error "No language defined!"
#endif

namespace caddie
{
    namespace msg
    {
        namespace Glf
        {
            const char* sHole = MESSAGE_DEF(
                "Hole",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sRepeatHole = MESSAGE_DEF(
                "Repeat Hole",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sPinType = MESSAGE_DEF(
                "Pin Type",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sWindDirection = MESSAGE_DEF(
                "Wind Direction",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sWindSpeed = MESSAGE_DEF(
                "Wind Speed (mph)",
                "Wind Speed (m/s)",
                "Wind Speed (m/s)",
                "Wind Speed (m/s)"
            );

            const char* sWindSpeedRange = MESSAGE_DEF(
                "Wind Speed Range",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sApplyRestart = MESSAGE_DEF(
                "Apply and Restart",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sQuitGame = MESSAGE_DEF(
                "Quit Game",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );
        }
    }
}