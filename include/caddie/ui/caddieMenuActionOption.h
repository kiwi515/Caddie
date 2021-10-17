#ifndef CADDIE_UI_MENU_ACTION_OPTION_H
#define CADDIE_UI_MENU_ACTION_OPTION_H
#include "types_caddie.h"
#include "caddieMenuOptionBase.h"

namespace caddie
{
    class MenuActionOption : public MenuOptionBase
    {
    public:
        // True return = toggle menu visibility after action
        typedef bool (* Action)();

        MenuActionOption(const char *name, Action action) : MenuOptionBase(name), mAction(action) {}
        virtual ~MenuActionOption() {}

        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

        virtual bool OnConfirm() const { return (*mAction)(); }

        virtual MenuOptionBase& operator++(int) { return *this; }
        virtual MenuOptionBase& operator--(int) { return *this; }

    private:
        Action mAction;
    };
}

#endif