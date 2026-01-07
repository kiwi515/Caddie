#include "types_caddie.h"

namespace caddie {
namespace {

/**
 * @brief Remove AB check
 */
bool IsABCheckAll() { return true; }

#if CADDIE_REGION_NTSC_U
kmBranch(0x8026a298, IsABCheckAll);
#elif CADDIE_REGION_PAL
kmBranch(0x8026a5b8, IsABCheckAll);
#endif

} // namespace
} // namespace caddie
