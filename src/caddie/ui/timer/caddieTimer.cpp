#include "caddie/ui/timer/caddieTimer.h"
#include <cstdio>
#include <cstring>

#include <nw4r/math.h>

namespace caddie {

Timer::Timer()
    : mRunning(false),
      mTimerValue(0),
      mFrozenValue(0),
      mFrozenDuration(0),
      mTextBox() {
          mTextBox.SetText("0.00");
          mTextBox.SetPosition(sTimerPos);
      }

const nw4r::math::VEC2 Timer::sTimerPos(8.0f, 8.0f);

Timer::~Timer() {}

void Timer::Start() {
    mRunning = true;
}

void Timer::Stop() {
    mRunning = false;
}

void Timer::Reset() {
    mTimerValue = 0;
    mFrozenValue = 0;
    mFrozenDuration = 0;
}

void Timer::Freeze(u32 duration) {
    mFrozenValue = mTimerValue;
    mFrozenDuration = duration;
}

void Timer::Calc() {
    if (mFrozenDuration > 0) {
        --mFrozenDuration;
    }

    if (mRunning) {
        ++mTimerValue;
    }

    u32 valueToDisplay = mFrozenDuration > 0 ? mFrozenValue : mTimerValue;
    mTextBox.SetTextFmt("%.2f", valueToDisplay / 60.0f);
}

void Timer::Draw() {
    mTextBox.Draw();
}

}