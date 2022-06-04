#ifndef CADDIE_UI_MENU_OPTION_H
#define CADDIE_UI_MENU_OPTION_H
#include "types_caddie.h"
#include "caddieLinkList.h"
#include "caddieTextBox.h"

namespace caddie
{
    /**
     * @brief Menu option interface
     */
    class IMenuOption : public Pane
    {
    public:
        static u32 GetNodeOffset() { return offsetof(IMenuOption, mNode); }

        IMenuOption(const char* name) :
            mIsEnabled(true)
        {
            // Option name
            mNameText.SetText(name);

            // Outline stroke
            mNameText.SetStroke(TextBox::STROKE_OUTLINE);
            mValueText.SetStroke(TextBox::STROKE_OUTLINE);

            // Append textboxes for drawing
            AppendChild(&mNameText);
            AppendChild(&mValueText);
        }
        
        virtual ~IMenuOption()
        {
        }

        virtual void DrawSelf() const
        {
        }

        virtual void Increment() = 0;
        virtual void Decrement() = 0;
        virtual void Validate() = 0;

        virtual void UpdateString() = 0;

        virtual void SaveChanges() = 0;
        virtual void DeleteChanges() = 0;

        virtual void OnClick() = 0;

        const char* GetName() const { return mNameText.GetText(); }
        void SetName(const char* name) { mNameText.SetText(name); }

        nw4r::ut::Color GetTextColor() const { return mNameText.GetTextColor(); }
        void SetTextColor(nw4r::ut::Color color)
        {
            mNameText.SetTextColor(color);
            mValueText.SetTextColor(color);
        }

        nw4r::ut::Color GetStrokeColor() const { return mNameText.GetStrokeColor(); }
        void SetStrokeColor(nw4r::ut::Color color)
        {
            mNameText.SetStrokeColor(color);
            mValueText.SetStrokeColor(color);
        }

        void SetPosition(nw4r::math::VEC2 pos)
        {
            CADDIE_ASSERT_EX(false, "Not implemented. Use SetOptionPosition");
        }

        nw4r::math::VEC2 GetOptionPosition() const
        {
            return mNameText.GetPosition();
        }
        void SetOptionPosition(nw4r::math::VEC2 pos, f32 width)
        {
            mNameText.SetPosition(nw4r::math::VEC2(pos.mCoords.x, pos.mCoords.y));
            mValueText.SetPosition(nw4r::math::VEC2(pos.mCoords.x + width, pos.mCoords.y));
        }

        bool IsEnabled() const { return mIsEnabled; }
        void SetEnabled(bool enable)
        {
            mIsEnabled = enable;
            SetTextColor(enable ? sEnabledTextColor : sDisabledTextColor);
            SetStrokeColor(enable ? sEnabledStrokeColor : sDisabledStrokeColor);
            UpdateString();
        }

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    protected:
        //! @brief Option name
        TextBox mNameText;
        //! @brief Option value
        TextBox mValueText;
        //! @brief Enable option
        bool mIsEnabled;

    private:
        static const nw4r::ut::Color sEnabledTextColor;
        static const nw4r::ut::Color sDisabledTextColor;
        static const nw4r::ut::Color sEnabledStrokeColor;
        static const nw4r::ut::Color sDisabledStrokeColor;
    };

    /**
     * @brief Menu option with integer value
     */
    class MenuIntOption : public IMenuOption
    {
    public:
        MenuIntOption(const char* name, int min, int max, int initial = 0x7FFFFFFF) :
            IMenuOption(name),
            mMin(min),
            mMax(max)
        {
            // Initial unused
            if (initial == 0x7FFFFFFF) {
                initial = mMin;
            }

            // Initialized saved/unsaved values
            SetUnsavedValue(initial);
            SaveChanges();
        }

        virtual ~MenuIntOption()
        {
        }

        virtual void Increment()
        {
            if (!mIsEnabled) {
                return;
            }

            int next = mValue + 1;
            if (next > mMax) {
                next = mMin;
            }
            SetUnsavedValue(next);
        }

        virtual void Decrement()
        {
            if (!mIsEnabled) {
                return;
            }
            
            int next = mValue - 1;
            if (next < mMin) {
                next = mMax;
            }
            SetUnsavedValue(next);
        }

        int GetMax() const { return mMax; }
        void SetMax(int max)
        {
            mMax = max;
            Validate();
        }

        int GetMin() const { return mMin; }
        void SetMin(int min)
        {
            mMin = min;
            Validate();
        }

        void SetRange(int min, int max)
        {
            SetMin(min);
            SetMax(max);
        }

        int GetUnsavedValue() const { return mValue; }
        void SetUnsavedValue(int val)
        {
            mValue = val;
            UpdateString();
        }

        int GetSavedValue() const { return mSavedValue; }
        void SetSavedValue(int val)
        {
            mSavedValue = val;
            UpdateString();
        }

        virtual void Validate()
        {
            if (mValue > mMax) {
                SetUnsavedValue(mMax);
            }
            else if (mValue < mMin) {
                SetUnsavedValue(mMin);
            }
        }

        virtual void SaveChanges()
        {
            Validate();
            SetSavedValue(mValue);
        }

        virtual void DeleteChanges()
        {
            SetUnsavedValue(mSavedValue);
        }

        virtual void UpdateString()
        {
            if (mIsEnabled) {
                mValueText.SetTextFmt("%i", mValue);
            }
            else {
                mValueText.SetText("DISABLED");
            }
        }
        
        virtual void OnClick()
        {
        }

    private:
        //! @brief Minimum value
        int mMin;
        //! @brief Maximum value
        int mMax;
        //! @brief Current (unsaved) value
        int mValue;
        //! @brief Saved value
        int mSavedValue;
    };

    /**
     * @brief Menu option with boolean value
     */
    class MenuBoolOption : public MenuIntOption
    {
    public:
        MenuBoolOption(const char* name, bool initial = false) :
            MenuIntOption(name, 0, 1, initial)
        {
            // Initialized saved/unsaved values
            SetUnsavedValue(initial);
            SaveChanges();
        }

        virtual ~MenuBoolOption()
        {
        }

        virtual void UpdateString()
        {
            if (mIsEnabled) {
                mValueText.SetText(GetUnsavedValue() ? "Yes" : "No");
            }
            else {
                mValueText.SetText("DISABLED");
            }
        }
    };

    /**
     * @brief Menu option with enum value
     */
    class MenuEnumOption : public MenuIntOption
    {
    public:
        MenuEnumOption(const char *name, const char** values,
            int min, int max, int initial = 0) :
            MenuIntOption(name, min, max, initial),
            mValues(values)
        {
            // Initialize saved/unsaved values
            SetUnsavedValue(initial);
            SaveChanges();
        }

        virtual ~MenuEnumOption()
        {
        }

        virtual void UpdateString()
        {
            if (mIsEnabled) {
                mValueText.SetText(mValues[GetUnsavedValue()]);
            }
            else {
                mValueText.SetText("DISABLED");
            }
        }

        const char** GetEnumValues() const { return mValues; }
        void SetEnumValues(const char** values)
        {
            mValues = values;
            UpdateString();
        }

    private:
        //! @brief Enum value strings
        const char** mValues;
    };

    /**
     * @brief Menu option with click callback
     */
    class MenuActionOption : public IMenuOption
    {
    public:
        typedef void (*Action)(void* arg);

        MenuActionOption(const char* name, Action act, void* arg) :
            IMenuOption(name),
            mAction(act),
            mActionArg(arg)
        {
            // Action options have no value
            mValueText.SetText("");
        }

        virtual ~MenuActionOption()
        {
        }

        virtual void Increment()
        {
        }
        virtual void Decrement()
        {
        }

        virtual void Validate()
        {
        }

        virtual void UpdateString()
        {
        }

        virtual void SaveChanges()
        {
        }

        virtual void DeleteChanges()
        {
        }
        
        virtual void OnClick()
        {
            if (mAction != NULL) {
                mAction(mActionArg);
            }
        }

        Action GetAction() const { return mAction; }
        void SetAction(Action act) { mAction = act; }

        void* GetActionArg() const { return mActionArg; }
        void SetActionArg(void* arg) { mActionArg = arg; }

    private:
        Action mAction;
        void* mActionArg;
    };
}

#endif