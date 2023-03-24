#ifndef NW4R_DB_CONSOLE_H
#define NW4R_DB_CONSOLE_H
#include "types_nw4r.h"

namespace nw4r {
namespace db {
namespace detail {

struct ConsoleHead {
    char* text;                       // at 0x0
    u16 width;                        // at 0x4
    u16 height;                       // at 0x6
    u16 priority;                     // at 0x8
    u16 attr;                         // at 0xA
    u16 printTop;                     // at 0xC
    u16 printXPos;                    // at 0xE
    u16 ringTop;                      // at 0x10
    s32 ringTopLineCnt;               // at 0x14
    s32 viewTopLine;                  // at 0x18
    s16 viewPosX;                     // at 0x1C
    s16 viewPosY;                     // at 0x1E
    u16 viewLines;                    // at 0x20
    bool isVisible;                   // at 0x22
    u8 padding;                       // at 0x23
    ut::TextWriterBase<char>* writer; // at 0x24
    ConsoleHead* next;                // at 0x28
};

} // namespace detail

void Console_DrawDirect(detail::ConsoleHead*);

s32 Console_GetTotalLines(detail::ConsoleHead*);

} // namespace db
} // namespace nw4r

#endif
