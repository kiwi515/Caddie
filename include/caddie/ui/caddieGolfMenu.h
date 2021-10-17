#ifndef CADDIE_UI_GOLF_MENU_H
#define CADDIE_UI_GOLF_MENU_H
#include "types_caddie.h"
#include "caddieMenuBase.h"

namespace caddie
{
    class GolfMenu : public MenuBase
    {
    public:
        enum GolfMenuOptions
        {
            GOLFMENU_HOLE,
            GOLFMENU_SAVEEXIT,
            GOLFMENU_MAX
        };

        static GolfMenu * GetInstance()
        {
            static GolfMenu instance;
            return &instance;
        }

        virtual void Calc();
        virtual void Build();

        static bool Action_SaveAndExit();

    private:
        GolfMenu() : MenuBase() { Build(); }
        virtual ~GolfMenu() {}
    };
}

#endif