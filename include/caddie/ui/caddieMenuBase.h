#ifndef CADDIE_UI_MENU_BASE_H
#define CADDIE_UI_MENU_BASE_H
#include "types_caddie.h"
#include "caddieMenuOptionBase.h"

#include "ut_list.h"

#include <STL/string.h>

#define INPUT_HISTORY_SIZE 2

namespace caddie
{
    class MenuBase
    {
    public:
        MenuBase() : mIsVisible(false), mSelection(0), mOptionTimer(0), mSettingTimer(0), mInputHistoryIdx(0)
        {
            nw4r::ut::List_Init(&mOptions, offsetof(MenuOptionBase, mNode));
        }

        virtual ~MenuBase();
        virtual void Calc();
        virtual void Build() = 0;

        static void PauseCallback();

        void Draw(f32 baseX, f32 baseY) const;
        void DumpAll(f32 baseX, f32 baseY) const;
        virtual void DoTick();
        void BuildHistory();

        void PushBack(MenuOptionBase *option)
        {
            CADDIE_ASSERT(option != NULL);
            nw4r::ut::List_Append(&mOptions, option);
        }

        bool IsVisible() const { return mIsVisible; }
        void Show() { mIsVisible = true; }
        void Hide() { mIsVisible = false; }
        void Toggle() { mIsVisible = !mIsVisible; }

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

        MenuOptionBase * GetOption(int i) const
        {
            CADDIE_ASSERT(i < mOptions.mSize);
            return (MenuOptionBase *)nw4r::ut::List_GetNth(&mOptions, i);
        }

        MenuOptionBase * GetOption(const char *name) const
        {
            CADDIE_ASSERT(name != NULL);
            MenuOptionBase *node = NULL;
            while (node = (MenuOptionBase *)nw4r::ut::List_GetNext(&mOptions, node))
            {
                if (strcmp(name, node->GetName()) == 0) return node;
            }

            CADDIE_ASSERT(false);
            return NULL;
        }

        int GetNumOptions() const { return mOptions.mSize; }

    private:
        nw4r::ut::List mOptions;
        bool mIsVisible;
        int mSelection;
        int mOptionTimer;
        int mSettingTimer;
        u16 mInputHistoryIdx;
        u16 mInputHistory[INPUT_HISTORY_SIZE];
    };
}

#endif