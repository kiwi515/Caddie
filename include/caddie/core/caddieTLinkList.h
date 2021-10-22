#ifndef CADDIE_CORE_T_LINKLIST_H
#define CADDIE_CORE_T_LINKLIST_H
#include "types_caddie.h"

namespace caddie
{
    template <typename T, int ofs>
    class TLinkList
    {
    public:
        struct Node
        {
            Node() : mNext(NULL), mPrev(NULL) {}
            ~Node() {}

            inline T * GetElem() const { return (T *)((char *)this + ofs); }

            Node *mNext;
            Node *mPrev;
        };

        struct Iterator
        {
            Iterator(Node *node) : mNode(node) {}
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
                CADDIE_BREAKPOINT;
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

            T * operator->() const { return mNode->GetElem(); }
            T & operator*() const { return *mNode->GetElem(); }

            bool operator==(Iterator rhs) const { return (mNode == rhs.mNode); }
            bool operator!=(Iterator rhs) const { return (mNode != rhs.mNode); }

            void operator=(Iterator rhs) { mNode = rhs.mNode; }
            void operator=(Node *rhs) { mNode = rhs; }

            Node *mNode;
        };

        TLinkList() : mHead(NULL), mTail(NULL), mSize(0) {}
        ~TLinkList() { Clear(); }

        Iterator Begin() const
        {
            CADDIE_ASSERT(mHead != NULL);
            return Iterator(mHead);
        }

        Iterator End() const
        {
            CADDIE_ASSERT(mTail != NULL);
            return Iterator(mTail);
        }

        T * Front() const
        {
            return &*Begin();
        }

        T * Back() const
        {
            return &*End();
        }

        T * At(int n) const
        {
            Iterator it = Begin();
            while (n-- > 0) it++;
            return &*it;
        }

        u32 Size() const { return mSize; }
        bool IsEmpty() const { return (mSize == 0); }
        
        void Prepend(T *obj)
        {
            CADDIE_ASSERT(obj != NULL);
            Node *n = GetNodeFromElem(obj);

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

        void Append(T *obj)
        {
            CADDIE_ASSERT(obj != NULL);
            Node *n = GetNodeFromElem(obj);

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

        void Insert(Iterator it, T *obj)
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
                Node *before = it.mNode->mPrev;
                Node *after = it.mNode->mNext;

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
        inline Node * GetNodeFromElem(T *elem) { return (Node *)((char *)elem - ofs); }
        void Insert(Iterator it, Node *node);

    private:
        Node *mHead;
        Node *mTail;
        u32 mSize;
    };
}

#endif