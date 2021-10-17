#include "caddieSplash.h"
#include "caddieDebug.h"

#include <Sp2Util.h>

#define CW_BUILD GETSTR(__CWCC__) "_" GETSTR(__CWBUILD__)

#ifdef NDEBUG
const char *CADDIE_BUILD = "Caddie (RELEASE): " __DATE__ " " __TIME__ " (" CW_BUILD ")";
#else
const char *CADDIE_BUILD = "Caddie (DEBUG): " __DATE__ " " __TIME__ " (" CW_BUILD ")";
#endif

#define COLOR_SPLASH_TEXT 0xFFFF0000
#define COLOR_SPLASH_SHADOW 0xFF000000

namespace caddie
{
    void ShowSplash()
    {
        Sp2::PrintOutline(CADDIE_BUILD, COLOR_SPLASH_TEXT, COLOR_SPLASH_SHADOW, true, 400.0f, 20.0f);
    }
    kmBranch(0x801c3490, &ShowSplash);
}