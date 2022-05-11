#ifndef CADDIE_CORE_LINKLIST_H
#define CADDIE_CORE_LINKLIST_H
#include "types_caddie.h"

namespace caddie
{
    struct TLinkListNode
    {
        TLinkListNode() : mNext(NULL), mPrev(NULL) {}
        ~TLinkListNode() {}

        TLinkListNode* mNext;
        TLinkListNode* mPrev;
    };

    template <typename T>
    class TLinkList
    {
    public:
        static inline TLinkListNode* GetNodeFromElem(T* elem) { return (TLinkListNode* )((char*)elem + T::GetNodeOffset()); }
        static inline T* GetElemFromNode(TLinkListNode* node) { return (T*)((char*)node - T::GetNodeOffset()); }

        struct Iterator
        {
            Iterator(TLinkListNode* node) : mNode(node) {}
            ~Iterator() {}

            Iterator operator++()
            {
                mNode = mNode->mNext;
                return *this;
            }
            Iterator operator--()
            {
                mNode = mNode->mPrev;
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator curr = Iterator(mNode);
                mNode = mNode->mNext;
                return curr;
            }
            Iterator operator--(int)
            {
                Iterator curr = Iterator(mNode);
                mNode = mNode->mPrev;
                return curr;                
            }

            T* operator->() const { return GetElemFromNode(mNode); }
            T& operator*() const { return *GetElemFromNode(mNode); }

            bool operator==(Iterator rhs) const { return (mNode == rhs.mNode); }
            bool operator!=(Iterator rhs) const { return (mNode != rhs.mNode); }

            void operator=(Iterator rhs) { mNode = rhs.mNode; }
            void operator=(TLinkListNode* rhs) { mNode = rhs; }

            TLinkListNode* mNode;
        };

        TLinkList() : mHead(NULL), mTail(NULL), mSize(0) {}
        ~TLinkList() { Clear(); }

        u32 Size() const { return mSize; }
        bool IsEmpty() const { return (mSize == 0); }

        Iterator Begin() const
        {
            return Iterator(mHead);
        }

        Iterator End() const
        {
            // Iterator is only designed to go forward for now
            return Iterator(NULL);
        }

        T* Front() const
        {
            return &*Begin();
        }

        T* Back() const
        {
            return &*At(mSize - 1);
        }

        T* At(int n) const
        {
            Iterator it = Begin();
            while (n-- > 0) it++;
            return &*it;
        }
        
        void Prepend(T* obj)
        {
            CADDIE_ASSERT(obj != NULL);
            TLinkListNode* n = GetNodeFromElem(obj);

            if (mHead == NULL)
            {
                mHead = n;
                mTail = mHead;
            }
            else
            {
                mHead->mPrev = n;
                n->mNext = mHead;
                mHead = n;
            }

            mSize++;
        }

        void Append(T* obj)
        {
            CADDIE_ASSERT(obj != NULL);
            TLinkListNode* n = GetNodeFromElem(obj);

            if (mTail == NULL)
            {
                mTail = n;
                mHead = mTail;
            }
            else
            {
                mTail->mNext = n;
                n->mPrev = mTail;
                mTail = n;
            }

            mSize++;
        }     

        void Insert(Iterator it, T* obj)
        {
            CADDIE_ASSERT(it.mNode != NULL);
            CADDIE_ASSERT(obj != NULL);

            if (it.mNode == mHead)
            {
                Prepend(obj);
            }
            else if (it.mNode == mTail)
            {
                Append(obj);
            }
            else
            {
                Insert(it, GetNodeFromElem(obj));
            }
        }

        void Remove(Iterator it)
        {
            CADDIE_ASSERT(it.mNode != NULL);

            if (it.mNode == mHead)
            {
                mHead = mHead->mNext;
                mSize--;
            }
            else if (it.mNode == mTail)
            {
                mTail = mTail->mPrev;
                mSize--;
            }
            else
            {
                TLinkListNode* before = it.mNode->mPrev;
                TLinkListNode* after = it.mNode->mNext;

                before->mNext = after;
                after->mPrev = before;
                mSize--;
            }
        }

        void Remove(Iterator start, Iterator end)
        {
            while (start != end)
            {
                Remove(start++);
            }
        }

        void Clear()
        {
            Remove(Begin(), End());
        }

    private:
        void Insert(Iterator it, TLinkListNode* node)
        {
            CADDIE_ASSERT(node != NULL);
            
            TLinkListNode* after = it.mNode;
            TLinkListNode* before = after->mPrev;
            CADDIE_ASSERT_EX(before != NULL, "List is broken!!!\n");

            before->mNext = node;
            node->mPrev = before;
            after->mPrev = node;
            node->mNext = after;

            mSize++;
        }

    private:
        TLinkListNode* mHead;
        TLinkListNode* mTail;
        u32 mSize;
    };
}

#endif