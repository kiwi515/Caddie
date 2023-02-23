#ifndef CADDIE_WIDE_TEXT_WRITER_H
#define CADDIE_WIDE_TEXT_WRITER_H
#include "types_caddie.h"

#include <nw4r/ut.h>

namespace caddie {

/**
 * @brief Wide text (wchar_t) writer. RP engine implements both but their wide
 * text writer gets deadstripped
 */
class WideTextWriter : public nw4r::ut::TextWriterBase<wchar_t> {
public:
    static WideTextWriter& GetInstance() {
        static WideTextWriter instance;
        return instance;
    }

    void Begin();
    void End();

    void Printf(f32 x, f32 y, const wchar_t* msg, ...);

private:
    WideTextWriter();
    virtual ~WideTextWriter();

private:
    bool mRendering;
};

} // namespace caddie

#endif
