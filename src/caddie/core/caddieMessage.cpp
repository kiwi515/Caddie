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
            const char* sHoleOption = MESSAGE_DEF(
                "Hole",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sRepeatHoleOption = MESSAGE_DEF(
                "Repeat Hole",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sPinTypeOption = MESSAGE_DEF(
                "Pin Type",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sWindDirectionOption = MESSAGE_DEF(
                "Wind Direction",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sWindSpeedOption = MESSAGE_DEF(
                "Wind Speed (mph)",
                "Wind Speed (m/s)",
                "Wind Speed (m/s)",
                "Wind Speed (m/s)"
            );

            const char* sWindSpeedRangeOption = MESSAGE_DEF(
                "Wind Speed Range",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sApplyRestartOption = MESSAGE_DEF(
                "Apply and Restart",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );

            const char* sQuitGameOption = MESSAGE_DEF(
                "Quit Game",
                "Not Localized",
                "Not Localized",
                "Not Localized"
            );
        }
    }
}