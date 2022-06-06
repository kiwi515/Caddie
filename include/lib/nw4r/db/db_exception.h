#ifndef NW4R_DB_EXCEPTION_H
#define NW4R_DB_EXCEPTION_H
#include "types_nw4r.h"

#include <OS/OSContext.h>

namespace nw4r {
namespace db {

void Exception_Printf_(const char*, ...);

void ShowFloat_(const OSContext*);

} // namespace db
} // namespace nw4r

#endif
