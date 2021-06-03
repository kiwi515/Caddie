#ifndef SP2_GLF_DEFINE_H
#define SP2_GLF_DEFINE_H

namespace Glf
{
    enum GameMode
    {
        GM_RESORT_NINE = 9,
        GM_RESORT_A = 10,
        GM_RESORT_B = 11,
        GM_RESORT_C = 12,
        GM_CLASSIC_NINE = 13,
        GM_CLASSIC_A = 14,
        GM_CLASSIC_B = 15,
        GM_CLASSIC_C = 16,
        GM_EIGHTEEN_HOLE = 17,
        GM_SPECIAL = 18
    };

    enum CourseSelBtn
    {
        BTN_RESORT_A,
        BTN_RESORT_B,
        BTN_RESORT_C,
        BTN_CLASSIC_A,
        BTN_CLASSIC_B,
        BTN_CLASSIC_C,
        BTN_SPECIAL,
        BTN_RESORT_NINE,
        BTN_CLASSIC_NINE,
        BTN_EIGHTEEN_HOLE
    };
}

#endif