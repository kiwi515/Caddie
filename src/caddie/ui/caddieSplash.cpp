#include "types_caddie.h"
#include "caddieSplash.h"
#include "caddieDebug.h"

#include <Sp2Util.h>

#ifdef NDEBUG
const char *CADDIE_BUILD = "Caddie (RELEASE): " __DATE__ " " __TIME__;
#else
const char *CADDIE_BUILD = "Caddie (DEBUG): " __DATE__ " " __TIME__;
#endif

#define COLOR_SPLASH_TEXT 0xFFFF0000
#define COLOR_SPLASH_SHADOW 0xFF000000

namespace caddie
{
    void ShowSplash()
    {
        char buf[512];
        sprintf(buf, "%s (%.1f KB free)\n", CADDIE_BUILD, (MemManager::GetFreeSize() / KB_AS_B));
        Sp2::PrintOutline(buf, COLOR_SPLASH_TEXT, COLOR_SPLASH_SHADOW, true, 400.0f, 20.0f);
    }
    kmBranch(0x801c3490, &ShowSplash);
}