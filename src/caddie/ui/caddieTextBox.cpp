#include "caddieTextBox.h"
#include <Sports2/Sp2Util.h>
#include <string.h>

namespace caddie
{
    TextBox::TextBox() :
        mTextBuffer(NULL)
    {
    }

    TextBox::~TextBox()
    {
        if (mTextBuffer != NULL) {
            delete mTextBuffer;
            mTextBuffer = NULL;
        }
    }

    /**
     * @brief Draw textbox
     */
    void TextBox::DrawSelf() const
    {
        CADDIE_LOG("TextBox::DrawSelf:\n");
        CADDIE_LOG_EX("    Name: %s\n", mTextBuffer);
        CADDIE_LOG_EX("    ARGB: %08X\n", GetARGB());
        CADDIE_LOG_EX("    Pos: (%.2f, %.2f)\n", mPos.mCoords.x, mPos.mCoords.y);
        CADDIE_LOG_EX("    Scale: %.2f\n", mScale);

        Sp2::Print(mTextBuffer, GetARGB(), false, mPos.mCoords.x, mPos.mCoords.y, mScale);
    }

    /**
     * @brief Set textbox text
     * 
     * @param str New text
     */
    void TextBox::SetText(const char* str)
    {
        const size_t len = strlen(str);

        if (mTextBuffer != NULL) {
            const size_t myLen = strlen(mTextBuffer);

            // Use existing buffer if possible
            if (len <= myLen) {
                strncpy(mTextBuffer, str, len);
            }
            else {
                // Reallocate buffer
                delete mTextBuffer;
                mTextBuffer = new char[len + 1];
                strncpy(mTextBuffer, str, len);
            }
        }
        else {
            // No existing buffer to use
            mTextBuffer = new char[len + 1];
            strncpy(mTextBuffer, str, len);
        }

        // Terminate string
        mTextBuffer[len] = '\0';
    }

    /**
     * @brief Set textbox text with format string
     * 
     * @param str Format string
     * @param ... Extra args
     */
    void TextBox::SetTextFmt(const char* str, ...)
    {
        char msg_buf[512];
        va_list list;

        va_start(str, list);
        vsnprintf(msg_buf, sizeof(msg_buf), str, list);
        va_end(list);

        SetText(msg_buf);
    }
}