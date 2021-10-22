#ifndef CADDIE_GAME_GOLF_MENU_H
#define CADDIE_GAME_GOLF_MENU_H
#include "types_caddie.h"
#include "caddieMenuBase.h"
#include "caddieMenuOptionBase.h"

namespace caddie
{
    class GolfMenu : public MenuBase
    {
    public:
        enum PinOptions
        {
            PIN_FROMSCORE,
            PIN_RANDOM,
            PIN_MAX
        };

        static GolfMenu * GetInstance()
        {
            static GolfMenu instance;
            return &instance;
        }

        virtual void Build();
        virtual void Calc();

        static void ApplyHoleSettings();
        static void ApplyWindSettings();
        static void ApplyPinSettings();

    private:
        static MenuOptionBase::MenuCommand Action_SaveReload();
        static MenuOptionBase::MenuCommand Action_QuitGame();

    private:
        GolfMenu() : MenuBase() { Build(); }
        virtual ~GolfMenu() {}

        static const char *sWindDirections[];
        static const char *sPinTypes[];
        static const char *sSpecialPinTypes[];
    };
}

#endif