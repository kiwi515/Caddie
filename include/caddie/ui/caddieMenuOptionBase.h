#ifndef CADDIE_UI_MENU_OPTION_BASE_H
#define CADDIE_UI_MENU_OPTION_BASE_H
#include "types_caddie.h"

#include "ut_list.h"

#define COLOR_DISABLED 0xFF8E8E8E

namespace caddie
{
    class MenuOptionBase
    {
    public:
        MenuOptionBase(const char *name) : mName(name), mIsEnabled(true) {}
        virtual ~MenuOptionBase() {}
        
        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const = 0;
        virtual MenuOptionBase& operator++(int) = 0;
        virtual MenuOptionBase& operator--(int) = 0;

        virtual void SaveState() = 0;
        virtual void LoadState() = 0;

        virtual bool OnConfirm() const = 0;

        const char * GetName() const { return mName; }
        bool IsEnabled() const { return mIsEnabled; }
        void SetEnabled(bool enable) { mIsEnabled = enable; }

    public:
        nw4r::ut::Node mNode;
    private:
        const char *mName;
        bool mIsEnabled;
    };
}

#endif