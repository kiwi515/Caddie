#include "caddieTextBox.h"
#include <Sports2/Sp2Util.h>
#include <string.h>

using namespace Sp2;

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
        Print(mTextBuffer, GetARGB(), false, mPos.mCoords.x, mPos.mCoords.y, mScale);
    }

    /**
     * @brief Set textbox text
     * 
     * @param str New text
     */
    void TextBox::SetText(const char* str)
    {
        if (mTextBuffer != NULL) {
            const size_t len = strlen(str);
            const size_t myLen = strlen(mTextBuffer);

            // Use existing buffer if possible
            if (len <= myLen) {
                strncpy(mTextBuffer, str, len);
                mTextBuffer[len] = '\0';
            }
            else {
                // Reallocate buffer
                delete mTextBuffer;
                mTextBuffer = new char[len];
                strncpy(mTextBuffer, str, len);
            }
        }
        else {
            // No existing buffer to use
            const size_t len = strlen(str);
            mTextBuffer = new char[len];
            strncpy(mTextBuffer, str, len);
        }
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

        va_start(msg, list);
        vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
        va_end(list);

        SetText(msg_buf);
    }
}