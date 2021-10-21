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
        enum MenuCommand
        {
            MENU_NO_OP,
            MENU_SHOW,
            MENU_HIDE
        };

        MenuOptionBase(const char *name) : mName(name), mIsEnabled(true) {}
        virtual ~MenuOptionBase() {}
        
        const char * GetName() const { return mName; }
        void SetName(const char *name) { mName = name; }

        bool IsEnabled() const { return mIsEnabled; }
        void SetEnabled(bool enable) { mIsEnabled = enable; }

        virtual MenuOptionBase& operator++(int) = 0;
        virtual MenuOptionBase& operator--(int) = 0;

        virtual void SaveChanges() = 0;
        virtual void DeleteChanges() = 0;

        virtual void Draw(f32 x, f32 y, f32 gapX, u32 color, u32 shadow = 0xFF000000) const = 0;

        virtual MenuCommand OnConfirm() const = 0;

    public:
        nw4r::ut::Node mNode;
    private:
        const char *mName;
        bool mIsEnabled;
    };
}

#endif