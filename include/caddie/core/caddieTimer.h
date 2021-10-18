#ifndef CADDIE_CORE_TIMER_H
#define CADDIE_CORE_TIMER_H

namespace caddie
{
    class Timer
    {
    public:
        Timer() : mIsRunning(false) {}
        virtual ~Timer() {}

        virtual void Start() { mIsRunning = true; }
        virtual void Update() = 0;
        virtual void Stop() { mIsRunning = false; }

        virtual u32 Elapsed() const = 0;

    private:
        bool mIsRunning;
    };
}

#endif