#include "caddieMenuOption.h"

namespace caddie
{
    template<>
    void MenuPrimOption<bool>::Increment()
    {
        SetUnsavedValue(!mValue);
    }

    template<>
    void MenuPrimOption<bool>::Decrement()
    {
        SetUnsavedValue(!mValue);
    }

    template<>
    void MenuPrimOption<bool>::Validate()
    {
    }

    template <>
    void MenuPrimOption<int>::UpdateString()
    {
        mValueText.SetTextFmt("%i", mValue);
    }

    template <>
    void MenuPrimOption<bool>::UpdateString()
    {
        mValueText.SetText(mValue ? "Yes" : "No");
    }

    const nw4r::ut::Color IMenuOption::sDisabledTextColor(142, 142, 142, 255);
    const nw4r::ut::Color IMenuOption::sDisabledStrokeColor(0, 0, 0, 255);
}