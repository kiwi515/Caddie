#ifndef RP_KERNEL_WIDE_TEXT_WRITER_H
#define RP_KERNEL_WIDE_TEXT_WRITER_H
#include "types_rp.h"

#include <RP/RPSystem/RPSysFontManager.h>
#include <nw4r/ut.h>

class RPSysWideTextWriter : public nw4r::ut::TextWriterBase<wchar_t> {
public:
    RPSysWideTextWriter(BOOL);
    ~RPSysWideTextWriter();

    void Begin();
    void End();

    void SetFont(RPSysFontManager::EResFont);

    void PrintfZeroCenter(f32 x, f32 y, const wchar_t* msg, ...);
    void PrintZeroCenter(f32 x, f32 y, const wchar_t* msg);

private:
    BOOL mIsRendering; // at 0x64
    bool BOOL_0x68;
};

#endif
