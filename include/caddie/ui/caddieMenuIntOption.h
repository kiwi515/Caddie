#ifndef CADDIE_UI_MENU_INT_OPTION_H
#define CADDIE_UI_MENU_INT_OPTION_H
#include "types_caddie.h"
#include "caddieMenuOptionBase.h"

#include <Sports2/Sp2Util.h>

#include <ut/ut_algorithm.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuIntOption : public MenuOptionBase
    {
    public:
        MenuIntOption(const char *name, int min, int max) : MenuOptionBase(name),
            mMin(min), mMax(max), mSavedValue(mMin), mUnsavedValue(mSavedValue) {}
        virtual ~MenuIntOption() {}

        virtual MenuOptionBase& operator++(int)
        {
            mUnsavedValue++;
            // Wrap around
            mUnsavedValue = (mUnsavedValue > mMax) ? mMin : mUnsavedValue;
            return *this;
        }

        virtual MenuOptionBase& operator--(int)
        {
            mUnsavedValue--;
            // Wrap around
            mUnsavedValue = (mUnsavedValue < mMin) ? mMax : mUnsavedValue;
            return *this;
        }

        virtual void SaveChanges() { mSavedValue = mUnsavedValue; }
        virtual void DeleteChanges() { mUnsavedValue = mSavedValue; }

        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

        virtual MenuCommand OnConfirm() const { return MENU_NO_OP; }

        int GetMin() const { return mMin; }
        void SetMin(int n)
        {
            mMin = n;
            SetSavedValue(mSavedValue);
            SetUnsavedValue(mUnsavedValue);
        }

        int GetMax() const { return mMax; }
        void SetMax(int n)
        {
            mMax = n;
            SetSavedValue(mSavedValue);
            SetUnsavedValue(mUnsavedValue);
        }

        void SetAllValue(int i)
        {
            SetSavedValue(i);
            SetUnsavedValue(i);
        }

        int GetSavedValue() const { return mSavedValue; }
        void SetSavedValue(int i) { mSavedValue = nw4r::ut::Clamp(mMin, mMax, i); }

        int GetUnsavedValue() const { return mUnsavedValue; }
        void SetUnsavedValue(int i) { mUnsavedValue = nw4r::ut::Clamp(mMin, mMax, i); }

    private:
        int mMin;
        int mMax;
        int mSavedValue;
        int mUnsavedValue;
    };
}

#endif