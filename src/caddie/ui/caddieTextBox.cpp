#include "caddieTextBox.h"

#include <Sports2/Sp2Util.h>
#include <cstdio>
#include <cstring>

namespace caddie {

TextBox::TextBox()
    : mStroke(STROKE_NONE),
      mIsCentered(false),
      mTextBuffer(NULL),
      mTextColor(255, 255, 255, 255),
      mStrokeColor(0, 0, 0, 255) {
    // Placeholder text
    SetText("TextBox");
}

TextBox::~TextBox() {
    delete mTextBuffer;
    mTextBuffer = NULL;
}

/**
 * @brief Draw textbox
 */
void TextBox::UserDrawSelf() const {
    CADDIE_ASSERT(mTextBuffer != NULL);

    switch (mStroke) {
    case STROKE_NONE:
        Sp2::Print(mTextBuffer, mTextColor.ToARGB(), mIsCentered, mPosition.x,
                   mPosition.y);
        break;
    case STROKE_OUTLINE:
        Sp2::PrintOutline(mTextBuffer, mTextColor.ToARGB(),
                          mStrokeColor.ToARGB(), mIsCentered, mPosition.x,
                          mPosition.y);
        break;
    case STROKE_SHADOW:
        Sp2::PrintShadow(mTextBuffer, mTextColor.ToARGB(),
                         mStrokeColor.ToARGB(), mIsCentered, mPosition.x,
                         mPosition.y);
        break;
    }
}

/**
 * @brief Reserve capacity in textbox buffer
 *
 * @param len Buffer size
 */
void TextBox::Reserve(size_t len) {
    // Buffer already exists
    if (mTextBuffer != NULL) {
        const size_t myLen = std::strlen(mTextBuffer);

        // Can we re-use it?
        if (len <= myLen) {
            return;
        }
    }

    // (Re)allocate buffer
    delete mTextBuffer;
    mTextBuffer = new char[len + 1];
}

/**
 * @brief Set textbox text
 *
 * @param str New text
 */
void TextBox::SetText(const char* str) {
    const size_t len = std::strlen(str);

    Reserve(len);
    std::strncpy(mTextBuffer, str, len);

    // Terminate string
    mTextBuffer[len] = '\0';
}

/**
 * @brief Set textbox text with format string
 *
 * @param str Format string
 * @param ... Extra args
 */
void TextBox::SetTextFmt(const char* str, ...) {
    char msg_buf[512];
    std::va_list list;

    va_start(list, str);
    std::vsnprintf(msg_buf, sizeof(msg_buf), str, list);
    va_end(list);

    SetText(msg_buf);
}

} // namespace caddie
