#ifndef NW4R_UT_TEXT_WRITER_BASE_H
#define NW4R_UT_TEXT_WRITER_BASE_H
#include "ut_CharWriter.h"
#include "ut_Font.h"
#include "ut_TagProcessorBase.h"
#include <types_nw4r.h>

namespace nw4r {
namespace ut {

template <typename T> class TextWriterBase : public CharWriter {
public:
    TextWriterBase();
    ~TextWriterBase();

    int GetTabWidth() const { return mTabWidth; }

    f32 GetLineHeight() const;

private:
    f32 mWidthLimit;                    // at 0x4C
    f32 mCharSpace;                     // at 0x50
    f32 mLineSpace;                     // at 0x54
    int mTabWidth;                      // at 0x58
    u32 mDrawFlag;                      // at 0x5C
    TagProcessorBase<T>* mTagProcessor; // at 0x60

    static TagProcessorBase<T> mDefaultTagProcessor;
    static T* mFormatBuffer;
    static u32 mFormatBufferSize;
};

} // namespace ut
} // namespace nw4r

#endif
