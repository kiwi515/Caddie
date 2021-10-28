#ifndef CADDIE_UI_MENU_ENUM_OPTION_H
#define CADDIE_UI_MENU_ENUM_OPTION_H
#include "types_caddie.h"
#include "caddieMenuIntOption.h"

#include <Sp2Util.h>

#include <STL/stdio.h>

namespace caddie
{
    class MenuEnumOption : public MenuIntOption
    {
    public:
        MenuEnumOption(const char *name, int min, int max, const char **table) : MenuIntOption(name, min, max), mTable(table) {}
        virtual ~MenuEnumOption() {}

        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const;

        virtual MenuOptionBase& operator++(int)
        {
            mUnsavedValue++;
            // Wrap around
            mUnsavedValue = (mUnsavedValue > mMax) ? mMin : mUnsavedValue;

            // Skip empty entries in table
            while (mTable[mUnsavedValue] == NULL)
            {
                mUnsavedValue++;
                mUnsavedValue = (mUnsavedValue > mMax) ? mMin : mUnsavedValue;
            }

            return *this;
        }

        virtual MenuOptionBase& operator--(int)
        {
            mUnsavedValue--;
            // Wrap around
            mUnsavedValue = (mUnsavedValue < mMin) ? mMax : mUnsavedValue;

            // Skip empty entries in table
            while (mTable[mUnsavedValue] == NULL)
            {
                mUnsavedValue--;
                mUnsavedValue = (mUnsavedValue < mMin) ? mMax : mUnsavedValue;
            }

            return *this;
        }

        bool IsNullSelect() const { return mTable[mUnsavedValue] == NULL; }

        const char ** GetTable() const { return mTable; }
        void SetTable(const char **table) { mTable = table; }

    private:
        const char **mTable;
    };
}

#endif