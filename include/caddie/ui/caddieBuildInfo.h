#ifndef CADDIE_UI_BUILD_INFO_H
#define CADDIE_UI_BUILD_INFO_H
#include "caddieTextBox.h"

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

private:
    //! @brief Build info text position
    static const nw4r::math::VEC2 sBuildTextPos;
    //! @brief Build info text color
    static const nw4r::ut::Color sBuildTextColor;
};

} // namespace caddie

#endif
