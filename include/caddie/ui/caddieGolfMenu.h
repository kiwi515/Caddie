#ifndef CADDIE_UI_GOLF_MENU_H
#define CADDIE_UI_GOLF_MENU_H
#include "types_caddie.h"
#include "caddieMenuBase.h"

namespace caddie
{
    class GolfMenu : public MenuBase
    {
    public:
        static GolfMenu * GetInstance()
        {
            static GolfMenu instance;
            return &instance;
        }

        virtual void Calc();
        virtual void Build();

        static void OnSetPin();
        static bool Action_ApplySettings();
        static bool Action_QuitGame();

    private:
        GolfMenu() : MenuBase() { Build(); }
        virtual ~GolfMenu() {}

        static const char *sWindDirections[];
        static const char *sPinTypes[];
        static const char *sSpecialPinTypes[];
    };
}

#endif