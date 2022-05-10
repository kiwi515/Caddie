#ifndef CADDIE_TEST_UI_TEST_H
#define CADDIE_TEST_UI_TEST_H
#include "types_caddie.h"
#include "types_RP.h"

namespace caddie
{
    class UiTest
    {
    public:
        static void Configure(RPSysScene*);
        static void Calculate(RPSysScene*);
        static void UserDraw(RPSysScene*);
        static void Exit(RPSysScene*);

    private:
        static TextBox* sTextBox;
        static TextBox* sTextBoxOutline;
        static TextBox* sTextBoxShadow;
        static IMenuOption* sIntOption;
    };
}

#endif