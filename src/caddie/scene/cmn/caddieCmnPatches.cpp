#include "types_caddie.h"

namespace caddie {
namespace {

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

} // namespace
} // namespace caddie
