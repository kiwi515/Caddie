#ifndef SP2_GLF_DEFINE_H
#define SP2_GLF_DEFINE_H

namespace Sp2
{
    namespace Glf
    {
        static const u32 HOLE_MAX = 21;
        static const u32 WIND_MAX = 15;
        static const u32 PIN_MAX = 1;
        static const u32 PLAYER_MAX = 4;

        enum WindDir
        {
            SOUTH,
            SOUTHEAST,
            EAST,
            NORTHEAST,
            NORTH,
            NORTHWEST,
            WEST,
            SOUTHWEST,
            MAX_WIND_DIV
        };

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

        // For use with StaticMem during the Glf scene
        enum GlfStaticMem
        {
            VAR_GAMEMODE,
            VAR_NEXTHOLE,
            
            VAR_BLINDFLAG = 3,

            VAR_PACKEDWIND = 7,
        };

        struct PackedWind
        {
            inline u8 value() const { return (mSpeed << 3) | mDirection; }

            u8 mSpeed : 4;
            u8 mDirection : 3;
        };

        inline u8 PackWind(int direction, int speed)
        {
            PackedWind wind;

            wind.mDirection = direction;
            wind.mSpeed = speed;

            return wind.value();
        }
    }
}

#endif