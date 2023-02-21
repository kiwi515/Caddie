#ifndef CADDIE_UI_TEXT_BOX_H
#define CADDIE_UI_TEXT_BOX_H
#include "caddiePane.h"
#include "types_caddie.h"

#include <nw4r/ut.h>

namespace caddie {

namespace {

/**
 * @brief Convert NW4R color to ARGB format
 */
static inline u32 Nw4rToARGB(nw4r::ut::Color color) {
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b);
}

/**
 * @brief Convert NW4R color to RGBA format
 */
static inline u32 Nw4rToRGBA(nw4r::ut::Color color) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | (color.a);
}

} // namespace

/**
 * @brief UI textbox
 */
class TextBox : public Pane {
public:
    /**
     * @brief Text stroke types
     */
    enum EStroke { STROKE_NONE, STROKE_OUTLINE, STROKE_SHADOW };

public:
    TextBox();
    virtual ~TextBox();
    virtual void DrawSelf() const;

    EStroke GetStroke() const { return mStroke; }
    void SetStroke(EStroke st) { mStroke = st; }

    bool IsCentered() const { return mIsCentered; }
    void SetCentered(bool center) { mIsCentered = center; }

    const char* GetText() const { return mTextBuffer; }
    void SetText(const char* str);
    void SetTextFmt(const char* str, ...);

    nw4r::ut::Color GetTextColor() const { return mTextColor; }
    void SetTextColor(nw4r::ut::Color color) { mTextColor = color; }

    nw4r::ut::Color GetStrokeColor() const { return mStrokeColor; }
    void SetStrokeColor(nw4r::ut::Color color) { mStrokeColor = color; }

private:
    //! @brief Stroke type
    EStroke mStroke;
    //! @brief Center text
    bool mIsCentered;
    //! @brief String buffer (owned)
    char* mTextBuffer;
    //! @brief Text color
    nw4r::ut::Color mTextColor;
    //! @brief Stroke color
    nw4r::ut::Color mStrokeColor;
};

} // namespace caddie

#endif
