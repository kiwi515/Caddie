#ifndef CADDIE_UI_TEXTBOX_H
#define CADDIE_UI_TEXTBOX_H
#include "types_caddie.h"
#include "caddiePane.h"
#include <nw4r/ut/ut_Color.h>

namespace caddie
{
    /**
     * @brief UI textbox
     */
    class TextBox : public Pane
    {
    public:
        TextBox();
        virtual ~TextBox();
        virtual void DrawSelf() const;

        const char* GetText() const { return mTextBuffer; }
        void SetText(const char* str);
        void SetTextFmt(const char* str, ...);

        void SetTextColor(const nw4r::ut::Color& color) { mColor = color; }

    private:
        /**
         * @brief Get text color in ARGB format (for Sp2 print)
         */
        u32 GetARGB() const
        {
            return (mColor.a << 24) | (mColor.r << 16)
                | (mColor.g << 8) | (mColor.b);
        }

    private:
        //! @brief String buffer (owned)
        char* mTextBuffer;
        //! @brief Text color
        nw4r::ut::Color mColor;
    };
}

#endif