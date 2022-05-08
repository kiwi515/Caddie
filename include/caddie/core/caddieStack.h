#ifndef CADDIE_CORE_STACK_H
#define CADDIE_CORE_STACK_H
#include "types_caddie.h"
#include "caddieLinkList.h"
#include "caddieAssert.h"

namespace caddie
{
    template <typename T>
    class Stack
    {
    public:
        Stack() {}
        virtual ~Stack() {}

        void Push(T* elem)
        {
            CADDIE_ASSERT(elem != NULL);
            mData.Append(elem);
        }

        T* Pop()
        {
            CADDIE_ASSERT(mData.Size() > 0);
            T* elem = mData.Back();
            mData.Remove(mData.End());
            return elem;
        }

        T* Peek() const
        {
            return mData.Back();
        }

        u32 Size() const
        {
            return mData.Size();
        }

        bool IsEmpty() const
        {
            return Size() == 0;
        }

    private:
        TLinkList<T, offsetof(T, mNode)> mData;
    };
}

#endif