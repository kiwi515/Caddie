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
        virtual ~IMenuOption() {}

        virtual void DrawSelf() const {}

        virtual void Increment() = 0;
        virtual void Decrement() = 0;
        virtual void Validate() = 0;

        virtual void SaveChanges() = 0;
        virtual void DeleteChanges() = 0;

        virtual void OnClick() = 0;

        const char* GetName() const { return mNameText.GetText(); }
        void SetName(const char* name) { mNameText.SetText(name); }

        nw4r::ut::Color GetTextColor() const { return mNameText.GetTextColor(); }
        void SetTextColor(nw4r::ut::Color color)
        {
            if (!mIsEnabled) {
                color = sDisabledTextColor;
            }

            mNameText.SetTextColor(color);
            mValueText.SetTextColor(color);
        }

        nw4r::ut::Color GetStrokeColor() const { return mNameText.GetStrokeColor(); }
        void SetStrokeColor(nw4r::ut::Color color)
        {
            if (!mIsEnabled) {
                color = sDisabledStrokeColor;
            }

            mNameText.SetStrokeColor(color);
            mValueText.SetStrokeColor(color);
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
            if (!enable) {
                SetTextColor(sDisabledTextColor);
                SetStrokeColor(sDisabledStrokeColor);
            }
        }

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    protected:
        //! @brief Option name
        TextBox mNameText;
        //! @brief Option value
        TextBox mValueText;
        //! @brief Option name width
        f32 mNameWidth;
        //! @brief Enable option
        bool mIsEnabled;

    private:
        static const nw4r::ut::Color sDisabledTextColor;
        static const nw4r::ut::Color sDisabledStrokeColor;
    };

    typedef TLinkList<IMenuOption> MenuOptionList;
    typedef MenuOptionList::Iterator MenuOptionIterator;

    /**
     * @brief Menu option with primitive value
     */
    template <typename T>
    class MenuPrimOption : public IMenuOption
    {
    public:
        MenuPrimOption(const char* name, T min, T max, T initial = T()) :
            IMenuOption(name),
            mMin(min),
            mMax(max),
            mValue(initial)
        {
            UpdateString();
        }
        virtual ~MenuPrimOption() {}

        virtual void Increment()
        {
            mValue++;
            if (mValue >= mMax) {
                mValue = mMin;
            }
            UpdateString();
        }

        virtual void Decrement()
        {
            mValue--;
            if (mValue < mMin) {
                mValue = mMax - 1;
            }
            UpdateString();
        }

        virtual T GetUnsavedValue() const { return mValue; }
        virtual void SetUnsavedValue(T val)
        {
            mValue = val;
            UpdateString();
        }

        virtual T GetSavedValue() const { return mSavedValue; }
        virtual void SetSavedValue(T val)
        {
            mSavedValue = val;
            UpdateString();
        }

        virtual void Validate()
        {
            if (mValue >= mMax) {
                mValue = mMax - 1;
            }
            else if (mValue < mMin) {
                mValue = mMin;
            }
            UpdateString();
        }

        virtual void SaveChanges()
        {
            Validate();
            mSavedValue = mValue;
        }

        virtual void DeleteChanges()
        {
            mValue = mSavedValue;
            UpdateString();
        }

        virtual void UpdateString()
        {
        }
        
        virtual void OnClick()
        {
        }

    private:
        //! @brief Minimum value
        T mMin;
        //! @brief Maximum value
        T mMax;
        //! @brief Current (unsaved) value
        T mValue;
        //! @brief Saved value
        T mSavedValue;
    };

    template<>
    void MenuPrimOption<bool>::Increment()
    {
        mValue = !mValue;
    }

    template<>
    void MenuPrimOption<bool>::Decrement()
    {
        mValue = !mValue;
    }

    template<>
    void MenuPrimOption<bool>::Validate()
    {
    }

    template <>
    void MenuPrimOption<int>::UpdateString()
    {
        mValueText.SetTextFmt("%i", mValue);
    }

    template <>
    void MenuPrimOption<bool>::UpdateString()
    {
        mValueText.SetText(mValue ? "Yes" : "No");
    }

    /**
     * @brief Menu option with enum type
     */
    class MenuEnumOption : public MenuPrimOption<int>
    {
    public:
        // MenuEnumOption()
        // virtual ~MenuEnumOption()

        // TODO
        // virtual void Draw();
    };

    /**
     * @brief Menu option with click callback
     */
    class MenuActionOption : public IMenuOption
    {
    public:
        typedef void (*Action)();

        MenuActionOption(const char* name, Action act) :
            IMenuOption(name),
            mClickAction(act)
        {
            // Action options have no value
            mValueText.SetText("");
        }
        virtual ~MenuActionOption() {}

        virtual void Increment() {}
        virtual void Decrement() {}
        virtual void Validate() {}

        virtual void SaveChanges() {}
        virtual void DeleteChanges() {}
        
        virtual void OnClick()
        {
            if (mClickAction != NULL) {
                mClickAction();
            }
        }

        void SetClickAction(Action act) { mClickAction = act; }

    private:
        Action mClickAction;
    };
}

#endif