#ifndef RP_KERNEL_WIDE_TEXT_WRITER_H
#define RP_KERNEL_WIDE_TEXT_WRITER_H
#include "types_rp.h"

#include <nw4r/ut.h>

class RPSysWideTextWriter : public nw4r::ut::TextWriterBase<wchar_t> {
public:
    RPSysWideTextWriter(BOOL);
    ~RPSysWideTextWriter();

    void Printf(f32 x, f32 y, const char* msg, ...);

private:
    BOOL mIsRendering; // at 0x64
    bool BOOL_0x68;
};

#endif
