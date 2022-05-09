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
    class IMenuOption
    {
    public:
        IMenuOption(const char* name) :
            mIsEnabled(false)
        {
            mNameText.SetText(name);
        }
        virtual ~IMenuOption() {}

        virtual void Draw() const = 0;

        const char* GetName() const { return mNameText.GetText(); }
        void SetName(const char* name) { mNameText.SetText(name); }

        void SetNamePosition(const nw4r::math::VEC2& pos) { mNameText.SetPosition(pos); }
        void SetValuePosition(const nw4r::math::VEC2& pos) { mValueText.SetPosition(pos); }

        bool IsEnabled() const { return mIsEnabled; }
        void SetEnabled(bool enable) { mIsEnabled = enable; }

        virtual void Increment() = 0;
        virtual void Decrement() = 0;
        virtual void Validate() = 0;

        virtual void SaveChanges() = 0;
        virtual void DeleteChanges() = 0;

        virtual void OnClick() = 0;

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
    };

    typedef TLinkList<IMenuOption, offsetof(IMenuOption, mNode)> MenuOptionList;
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
            mValue(initial),
        {}
        virtual ~MenuPrimOption() {}

        virtual void Increment()
        {
            mValue++;
            if (mValue >= mMax) {
                mValue = mMin;
            }
        }

        virtual void Decrement()
        {
            mValue--;
            if (mValue <= mMin) {
                mValue = mMax;
            }
        }

        virtual void Validate()
        {
            if (mValue >= mMax) {
                mValue = mMax;
            }
            else if (mValue <= mMin) {
                mValue = mMin;
            }
        }

        virtual void SaveChanges()
        {
            Validate();
            mSavedValue = mValue;
        }

        virtual void DeleteChanges()
        {
            mValue = mSavedValue;
        }

        virtual void UpdateString()
        {
        }

        virtual void Draw() const
        {
            mNameText.Draw();
            mValueText.Draw();
        }
        
        virtual void OnClick() {}

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
    virtual void MenuPrimOption<bool>::Increment()
    {
        mValue = !mValue;
    }

    template<>
    virtual void MenuPrimOption<bool>::Decrement()
    {
        mValue = !mValue;
    }

    template<>
    virtual void MenuPrimOption<bool>::Validate()
    {
    }

    template <>
    virtual void MenuPrimOption<int>::UpdateString()
    {
        mValueText.SetTextFmt("%i", mValue);
    }

    template <>
    virtual void MenuPrimOption<bool>::UpdateString()
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
        // virtual void Draw() const;
    };

    /**
     * @brief Menu option with click callback
     */
    class MenuActionOption : public IMenuOption
    {
    public:
        typedef void (*Action)();

        MenuActionOption(const char* name, Action act) :
            IMenuOption(name)
        {}
        virtual ~MenuActionOption() {}

        virtual void Draw() const
        {
            mNameText.Draw();
        }

        virtual void Increment() {};
        virtual void Decrement() {};
        virtual void Validate() {};

        virtual void SaveChanges() {};
        virtual void DeleteChanges() {};
        
        virtual void OnClick()
        {
            if (mOnClick != NULL) {
                mOnClick();
            }
        }

        void SetOnClick(Action act) { mOnClick = act; }

    private:
        Action mOnClick;
    }
}

#endif