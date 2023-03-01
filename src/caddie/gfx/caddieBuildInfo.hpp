#ifndef CADDIE_UI_BUILD_INFO_H
#define CADDIE_UI_BUILD_INFO_H
#include "caddieMessage.hpp"
#include "caddieTextBox.hpp"

namespace caddie {

/**
 * @brief Text box displaying info about the current build of Caddie
 */
class BuildInfo : public TextBox {
public:
    static const char* GetBuildDate();
    static const char* GetBuildRegion();
    static const char* GetBuildTarget();

    BuildInfo();
    virtual ~BuildInfo() {}
    virtual void Calculate();

private:
    //! @brief Build info text position
    static const Vec2<f32> scTextPosition;
    //! @brief Build info text color
    static const Color scTextColor;
};

} // namespace caddie

#endif
