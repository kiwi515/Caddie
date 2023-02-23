#ifndef NW4R_UT_CHAR_WRITER_H
#define NW4R_UT_CHAR_WRITER_H
#include "ut_Color.h"

#include <nw4r/math.h>
#include <types_nw4r.h>

namespace nw4r {
namespace ut {

class CharWriter {
public:
    enum GradationMode { GRADMODE_NONE, GRADMODE_H, GRADMODE_V };

    struct ColorMapping {
        Color min; // at 0x0
        Color max; // at 0x4
    };

    struct VertexColor {
        Color tl; // at 0x0
        Color tr; // at 0x4
        Color bl; // at 0x8
        Color br; // at 0xC
    };

    struct TextColor {
        Color start;            // at 0x0
        Color end;              // at 0x4
        GradationMode gradMode; // at 0x8
    };

    struct TextureFilter {
        GXTexFilter atSmall; // at 0x0
        GXTexFilter atLarge; // at 0x4

        // TODO: Can this be implicitly generated?
        bool operator!=(const TextureFilter& other) const {
            return atSmall != other.atSmall || atLarge != other.atLarge;
        }
    };

    struct LoadingTexture {
        GXTexMapID slot; // at 0x0
        void* texture;   // at 0x4
        TextureFilter filter;

        // TODO: Can this be implicitly generated?
        bool operator!=(const LoadingTexture& other) const {
            return slot != other.slot || texture != other.texture ||
                   filter != other.filter;
        }

        void Reset() {
            slot = GX_TEXMAP_NULL;
            texture = 0;
        }
    };

public:
    CharWriter();
    ~CharWriter();

    void SetupGX();

    void SetFont(const Font& font) { mFont = &font; }

    void ResetColorMapping() {
        SetColorMapping(Color(0x00000000), Color(0xFFFFFFFF));
    }

    void SetColorMapping(Color min, Color max) {
        mColorMapping.min = min;
        mColorMapping.max = max;
    }

    void SetTextColor(Color start) { mTextColor.start = start; }

    void SetTextColor(Color start, Color end) {
        mTextColor.start = start;
        mTextColor.end = end;
    }

    void SetGradationMode(GradationMode mode) {
        mTextColor.gradMode = mode;
        UpdateVertexColor();
    }

    void SetScale(f32 x, f32 y) {
        mScale.x = x;
        mScale.y = y;
    }

    void SetCursor(f32 x, f32 y) {
        mCursorPos.x = x;
        mCursorPos.y = y;
    }

    void SetCursor(f32 x, f32 y, f32 z) {
        mCursorPos.x = x;
        mCursorPos.y = y;
        mCursorPos.z = z;
    }

    void UpdateVertexColor();

    void EnableLinearFilter(bool atSmall, bool atLarge);

private:
    ColorMapping mColorMapping; // at 0x0
    VertexColor mVertexColor;   // at 0x8
    TextColor mTextColor;       // at 0x18
    math::VEC2 mScale;          // at 0x24
    math::VEC3 mCursorPos;      // at 0x2C
    TextureFilter mFilter;      // at 0x38
    u8 _padding[2];             // at 0x40
    u8 mAlpha;                  // at 0x42
    bool mIsWidthFixed;         // at 0x43
    f32 mFixedWidth;            // at 0x44
    const Font* mFont;          // at 0x48

    static LoadingTexture mLoadingTexture;
};

} // namespace ut
} // namespace nw4r

#endif
