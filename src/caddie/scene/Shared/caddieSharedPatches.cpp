#include "types_caddie.hpp"

namespace caddie {
namespace Shared {

/**
 * @brief Remove AB check
 */
bool PatchABCheck() { return true; }
kmBranch(0x8026a298, PatchABCheck);

/**
 * @brief Remove Wii Remote warning screen before sport scenes
 */
bool PatchWarningLyt() { return true; }
kmBranch(0x8022eaf8, PatchWarningLyt);

} // namespace Shared
} // namespace caddie
