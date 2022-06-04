#include "caddieDebug.h"

#include <egg/core/eggController.h>
#include <egg/util/eggException.h>

namespace caddie {

void SetExceptionCallback() {
    // Empty button combo will always immediately show the exception handler.
    static u16 sExceptionCombo[] = {EGG::BTN_NONE};
    EGG::Exception::setUserCallback(sExceptionCombo);
}

} // namespace caddie
