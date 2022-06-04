#ifndef CADDIE_UI_BUILD_INFO_H
#define CADDIE_UI_BUILD_INFO_H
#include "caddieTextBox.h"

namespace caddie {

/**
 * @brief Text box displaying info about the build of Caddie
 */
class BuildInfo : public TextBox {
  public:
    BuildInfo();
    virtual ~BuildInfo() {}

  private:
    static const nw4r::math::VEC2 sBuildTextPos;
    static const nw4r::ut::Color sBuildTextColor;
};

} // namespace caddie

#endif
