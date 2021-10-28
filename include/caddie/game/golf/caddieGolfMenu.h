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
        enum WindDirOptions
        {
            DIR_SOUTH,
            DIR_SOUTHEAST,
            DIR_EAST,
            DIR_NORTHEAST,
            DIR_NORTH,
            DIR_NORTHWEST,
            DIR_WEST,
            DIR_SOUTHWEST,
            DIR_RANDOM,
            DIR_MAX
        };

        enum WindSpdOptions
        {
            SPD_RANDOM = 16,
            SPD_MAX
        };

        enum WindSpdRangeOptions
        {
            RANGE_0_10,  // 18H
            RANGE_0_5,   // A
            RANGE_5_10,  // B
            RANGE_10_15, // C
            RANGE_0_15   // SP
        };

        enum PinOptions
        {
            PIN_1,
            PIN_2,
            PIN_3,
            PIN_4,
            PIN_5,
            PIN_6,
            PIN_FROMSCORE,
            PIN_RANDOM_ALL,
            PIN_RANDOM_A,
            PIN_RANDOM_B,
            PIN_MAX
        };

        static GolfMenu * GetInstance()
        {
            static GolfMenu instance;
            return &instance;
        }

        virtual void Build();
        virtual void Calc();
        virtual void Reset();

        void Validate();

        static void ApplyHoleSettings();
        static void ApplyWindSettings();
        static void ApplyPinSettings();

    private:
        static MenuOptionBase::MenuCommand Action_SaveReload();
        static MenuOptionBase::MenuCommand Action_ReloadNoSave();
        static MenuOptionBase::MenuCommand Action_QuitGame();

    private:
        GolfMenu() : MenuBase() { Build(); }
        virtual ~GolfMenu() {}
    };
}

#endif