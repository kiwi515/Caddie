#include "types_caddie.h"

namespace caddie {
namespace {

/**
 * @brief Remove AB check
 */
bool PatchABCheck() { return true; }
kmBranch(0x8026a298, PatchABCheck);

} // namespace
} // namespace caddie
