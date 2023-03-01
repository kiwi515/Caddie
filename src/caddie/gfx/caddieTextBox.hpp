#ifndef CADDIE_UI_TEXT_BOX_H
#define CADDIE_UI_TEXT_BOX_H
#include "caddieColor.hpp"
#include "caddiePane.hpp"
#include "types_caddie.hpp"

#include <nw4r/ut.h>

namespace caddie {

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

    virtual void Configure() {}
    virtual void LoadResource() {}
    virtual void Reset() {}
    virtual void Calculate() {}
    virtual void UserDrawSelf() const;
    virtual void DebugDrawSelf() const {}
    virtual void Exit() {}

    EStroke GetStroke() const { return mStroke; }
    void SetStroke(EStroke st) { mStroke = st; }

    bool IsCentered() const { return mIsCentered; }
    void SetCentered(bool center) { mIsCentered = center; }

    const char* GetText() const { return mTextBuffer; }
    void SetText(const char* str);
    void SetTextFmt(const char* str, ...);

    Color GetTextColor() const { return mTextColor; }
    void SetTextColor(Color color) { mTextColor = color; }

    Color GetStrokeColor() const { return mStrokeColor; }
    void SetStrokeColor(Color color) { mStrokeColor = color; }

private:
    void Reserve(size_t len);

private:
    //! @brief Stroke type
    EStroke mStroke;
    //! @brief Center text
    bool mIsCentered;
    //! @brief String buffer (owned)
    char* mTextBuffer;
    //! @brief Text color
    Color mTextColor;
    //! @brief Stroke color
    Color mStrokeColor;
};

} // namespace caddie

#endif
