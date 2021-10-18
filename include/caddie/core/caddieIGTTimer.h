#ifndef CADDIE_CORE_IGT_TIMER_H
#define CADDIE_CORE_IGT_TIMER_H
#include "types_caddie.h"

#include "caddieTimer.h"

namespace caddie
{
    class IGTTimer : public Timer
    {
    public:
        IGTTimer() : mElapsed(0) {}
        virtual ~IGTTimer() {}

        virtual void Start()
        {
            Timer::Start();
            mElapsed = 0;
        }

        virtual void Update() { mElapsed++; }
        
        virtual void Stop()
        {
            Timer::Stop();
        }

    #ifdef CADDIE_REGION_USA
        virtual u32 Elapsed() const { return mElapsed; }
    #endif

    private:
        u32 mElapsed;
    };
}

#endif