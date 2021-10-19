#ifndef CADDIE_CORE_RTA_TIMER_H
#define CADDIE_CORE_RTA_TIMER_H
#include "types_caddie.h"

#include "caddieTimer.h"

#include <OS/OSTime.h>

namespace caddie
{
    class RTATimer : public Timer
    {
    public:
        RTATimer() : mStartTick(0), mEndTick(0) {}
        virtual ~RTATimer() {}

        virtual void Start()
        {
            Timer::Start();
            mStartTick = OSGetTick();
        }

        virtual void Update() {}

        virtual void Stop()
        {
            Timer::Stop();
            mEndTick = OSGetTick();
        }

        // TODO: ticks->seconds
        virtual u32 Elapsed() const { return mEndTick - mStartTick; }

        // TODO
        virtual void ToString(char *buf) const
        {

        }

    private:
        u32 mStartTick;
        u32 mEndTick;
    };
}

#endif