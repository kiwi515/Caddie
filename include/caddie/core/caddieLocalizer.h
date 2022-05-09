#ifndef CADDIE_CORE_LOCALIZER_H
#define CADDIE_CORE_LOCALIZER_H
#include "types_caddie.h"
#include "types_rp.h"

namespace caddie
{
    extern u32 sGameCode : 0x80000000;
    extern u16 sMakerCode : 0x80000004;

    class Localizer
    {
    public:
        enum Region
        {
            NTSC_U,
            PAL,
            NTSC_J,
            KOR,
            REGION_MAX
        };

        static Localizer* GetInstance()
        {
            static Localizer instance;
            return &instance;
        }

        Region GetGameRegion() const
        {
            CADDIE_ASSERT(sMakerCode == '01');

            switch(sGameCode)
            {
                case 'RZTE': return NTSC_U;
                case 'RZTP': return PAL;
                case 'RZTJ': return NTSC_J;
                case 'RZTK': return KOR;
                default: CADDIE_ASSERT_EX(false, "Invalid game region!!!");
            }
        }

        const char* Localize(const char* locale[REGION_MAX]) { return locale[GetGameRegion()]; }

        RPSysProjectLocal* GetRPLocale() const { return mRPLocale; }

    private:
        RPSysProjectLocal* mRPLocale;
    };
}

#endif