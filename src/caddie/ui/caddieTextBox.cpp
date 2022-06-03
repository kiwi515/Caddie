#include "caddieTextBox.h"
#include <Sports2/Sp2Util.h>
#include <string.h>

namespace caddie
{
    TextBox::TextBox() :
        mStroke(STROKE_NONE),
        mIsCentered(false),
        mTextBuffer(NULL),
        mTextColor(255, 255, 255, 255),
        mStrokeColor(0, 0, 0, 255)
    {
        // Placeholder text
        SetText("TextBox");
    }

    TextBox::~TextBox()
    {
        delete mTextBuffer;
        mTextBuffer = NULL;
    }

    /**
     * @brief Draw textbox
     */
    void TextBox::DrawSelf() const
    {
        CADDIE_ASSERT(mTextBuffer != NULL);

        switch(mStroke)
        {
            case STROKE_NONE:
                Sp2::Print(mTextBuffer, Nw4rToARGB(mTextColor), mIsCentered,
                    mPos.mCoords.x, mPos.mCoords.y);
                break;
            case STROKE_OUTLINE:
                Sp2::PrintOutline(mTextBuffer, Nw4rToARGB(mTextColor),
                    Nw4rToARGB(mStrokeColor), mIsCentered,
                    mPos.mCoords.x, mPos.mCoords.y);
                break;
            case STROKE_SHADOW:
                Sp2::PrintShadow(mTextBuffer, Nw4rToARGB(mTextColor),
                    Nw4rToARGB(mStrokeColor), mIsCentered,
                    mPos.mCoords.x, mPos.mCoords.y);
                break;
        }
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
            delete mTextBuffer;
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