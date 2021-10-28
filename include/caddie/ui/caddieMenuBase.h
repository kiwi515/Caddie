#ifndef CADDIE_UI_MENU_BASE_H
#define CADDIE_UI_MENU_BASE_H
#include "types_caddie.h"
#include "caddieMenuOptionBase.h"
#include "caddieTLinkList.h"

#include <STL/string.h>

#define GET_OPTION(type, name) ((type *)GetOption(name))
#define GET_OPTION_STATIC(__menu, type, name) ((type *)__menu->GetOption(name))

#define INPUT_HISTORY_SIZE 2

namespace caddie
{
    class MenuBase
    {
    public:
        typedef TLinkList<MenuOptionBase, offsetof(MenuOptionBase, mNode)> MenuOptionBaseList;

        MenuBase() : mOptions(), mIsVisible(false), mSelection(0), mOptionTimer(0), mSettingTimer(0), mInputHistoryIdx(0) {}
        virtual ~MenuBase() {}

        virtual void Build() = 0;
        virtual void Reset() = 0;
        virtual void Calc();

        void Draw(f32 baseX, f32 baseY) const;
        void DumpAll(f32 baseX, f32 baseY) const;
        virtual void DoTick();
        void BuildHistory();

        void PushBackOption(MenuOptionBase *option)
        {
            CADDIE_ASSERT(option != NULL);
            mOptions.Append(option);
        }

        void SaveChanges()
        {
            for (MenuOptionBaseList::Iterator it = mOptions.Begin(); it != mOptions.End(); it++)
            {
                it->SaveChanges();
            }
        }

        void DeleteChanges()
        {
            for (MenuOptionBaseList::Iterator it = mOptions.Begin(); it != mOptions.End(); it++)
            {
                it->DeleteChanges();
            }
        }

        bool IsVisible() const { return mIsVisible; }
        void Show() { mIsVisible = true; }
        void Hide()
        {
            mIsVisible = false;
            // Revert unsaved changes to the options when closing the menu
            DeleteChanges();
        }
        void Toggle() 
        {
            if (mIsVisible) Hide();
            else Show();
        }

        bool Pressed(u16 mask) const
        {
            int thisFrameIdx = mInputHistoryIdx - 1;
            if (thisFrameIdx < 0) thisFrameIdx = INPUT_HISTORY_SIZE - 1;
            return mInputHistory[thisFrameIdx] & mask;
        }

        bool PressedLastFrame(u16 mask) const
        {
            return mInputHistory[mInputHistoryIdx] & mask;
        }

        MenuOptionBase * GetOption(int n) const
        {
            CADDIE_ASSERT(n < mOptions.Size());

            MenuOptionBaseList::Iterator it = mOptions.Begin();
            for (int i = 0; i < n && it != mOptions.End(); i++, it++) {}
            return &*it;
        }

        MenuOptionBase * GetOption(const char *name) const
        {
            CADDIE_ASSERT(name != NULL);

            for (MenuOptionBaseList::Iterator it = mOptions.Begin(); it != mOptions.End(); it++)
            {
                if (strcmp(name, it->GetName()) == 0) return &*it;
            }

            CADDIE_ASSERT(false);
            return NULL;
        }

        const MenuOptionBaseList * GetOptions() const { return &mOptions; }
        MenuOptionBaseList * GetOptions() { return &mOptions; }

        int GetNumOptions() const { return mOptions.Size(); }

    private:
        MenuOptionBaseList mOptions;
        bool mIsVisible;
        int mSelection;
        int mOptionTimer;
        int mSettingTimer;
        u16 mInputHistoryIdx;
        u16 mInputHistory[INPUT_HISTORY_SIZE];
    };
}

#endif