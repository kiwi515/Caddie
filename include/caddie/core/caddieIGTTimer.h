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

        virtual void Update() { if (IsRunning()) mElapsed++; }
        
        virtual void Stop()
        {
            Timer::Stop();
        }

        virtual u32 Elapsed() const { return mElapsed; }
        void SetElapsed(s32 time) { mElapsed = time; }

    private:
        s32 mElapsed;
    };
}

#endif