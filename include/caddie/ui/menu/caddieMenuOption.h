#ifndef CADDIE_UI_MENU_OPTION_H
#define CADDIE_UI_MENU_OPTION_H
#include "types_caddie.h"
#include "caddieLinkList.h"

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
            SetName(name);
        }
        virtual ~IMenuOption() {}

        const char* GetName() const { return mName; }
        void SetName(const char* name) { mName = name; }

        bool IsEnabled() const { return mIsEnabled; }
        void SetEnabled(bool enable) { mIsEnabled = enable; }

        virtual void Increment() = 0;
        virtual void Decrement() = 0;
        virtual void Validate() = 0;

        virtual void SaveChanges() = 0;
        virtual void DeleteChanges() = 0;

        virtual void Draw() const = 0;
        
        virtual void OnClick() = 0;

    public:
        //! @brief Node for intrusive list
        TLinkListNode mNode;

    private:
        //! @brief Option name
        const char* mName;
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

        // TODO
        virtual void Draw() const;
        
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

    /**
     * @brief Menu option with enum type
     */
    class MenuEnumOption : public MenuPrimOption<int>
    {
    public:
        // MenuEnumOption()
        // virtual ~MenuEnumOption()

        // TODO
        virtual void Draw() const;
    };

    /**
     * @brief Menu option with click callback
     */
    class MenuActionOption : public IMenuOption
    {
    public:
        typedef void (*Action)();

        // MenuActionOption(const char* name, Action act)
        // virtual ~MenuActionOption()

        // TODO
        virtual void Draw() const;

        void SetOnClick(Action act) { mOnClick = act; }
        
        virtual void OnClick()
        {
            if (mOnClick != NULL) {
                mOnClick();
            }
        }

    private:
        Action mOnClick;
    }
}

#endif