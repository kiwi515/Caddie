#ifndef CADDIE_UI_MENU_OPTION_H
#define CADDIE_UI_MENU_OPTION_H
#include "types_caddie.h"
#include "caddieMenuOptionBase.h"

#include <Sp2Util.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuIntOption : public MenuOptionBase
    {
    public:
        MenuIntOption(const char *name, int min, int max) : MenuOptionBase(name), mMin(min), mMax(max), mValue(mMin) {}
        virtual ~MenuIntOption() {}
        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

        virtual bool OnConfirm() const { return false; }

        int GetMax() const { return mMax; }
        void SetMax(int n) { mMax = n; }

        int GetValue() const { return mValue; }
        void SetValue(int i) { mValue = i; }

        virtual MenuOptionBase& operator++(int)
        {
            if (++mValue > mMax) mValue = mMin;
            return *this;
        }

        virtual MenuOptionBase& operator--(int)
        {
            if (--mValue < mMin) mValue = mMax;
            return *this;
        }

    private:
        int mMin;
        int mMax;
        int mValue;
    };
}

#endif