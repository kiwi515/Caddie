#ifndef NW4R_UT_TEXT_WRITER_BASE_H
#define NW4R_UT_TEXT_WRITER_BASE_H
#include "ut_CharWriter.h"

#include <types_nw4r.h>

namespace nw4r {
namespace ut {

template <typename T> class TextWriterBase : public CharWriter {
public:
    TextWriterBase();
    ~TextWriterBase();

    f32 VPrintf(const T* msg, va_list args);

private:
    f32 mWidthLimit;                    // at 0x4C
    f32 mCharSpace;                     // at 0x50
    f32 mLineSpace;                     // at 0x54
    int mTabWidth;                      // at 0x58
    u32 mDrawFlag;                      // at 0x5C
    TagProcessorBase<T>* mTagProcessor; // at 0x60

    // static TagProcessorBase<T> mDefaultTagProcessor;
    static T* mFormatBuffer;
    static u32 mFormatBufferSize;
};

} // namespace ut
} // namespace nw4r

#endif
