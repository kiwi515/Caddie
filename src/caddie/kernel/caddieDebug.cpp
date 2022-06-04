#include "caddieDebug.h"

#include "eggException.h"
#include "eggController.h"

namespace caddie
{
    using namespace EGG;

    void SetExceptionCallback()
    {
        // Empty button combo will always immediately show the exception handler.
        static u16 sExceptionCombo[] = { BTN_NONE };
        Exception::setUserCallback(sExceptionCombo);
    }
}
