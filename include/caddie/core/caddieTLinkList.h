#ifndef CADDIE_CORE_T_LINKLIST_H
#define CADDIE_CORE_T_LINKLIST_H
#include "types_caddie.h"

namespace caddie
{
    template <typename T, int ofs>
    class TLinkList
    {
    public:
        class Node
        {
        public:
            Node() : mNext(NULL), mPrev(NULL) {}
            ~Node() {}

            Node * Next() const { return mNext; }
            Node * Prev() const { return mPrev; }

            void SetNext(Node *node) { mNext = node; }
            void SetPrev(Node *node) { mPrev = node; }

            inline T * GetElem() const { return (T *)((char *)this + ofs); }
        private:
            Node *mNext;
            Node *mPrev;
        };

        class Iterator
        {
        public:
            Iterator(Node *node) : mNode(node) {}
            ~Iterator() {}

            Iterator& operator++() { mNode = mNode->mNext; }
            Iterator& operator--() { mNode = mNode->mPrev; }
            Iterator& operator++(int)
            {
                Iterator curr = Iterator(mNode);
                mNode = mNode->mNext;
                return curr;
            }
            Iterator& operator--(int)
            {
                Iterator curr = Iterator(mNode);
                mNode = mNode->mPrev;
                return curr;                
            }

            T * operator->() { return mNode.GetElem(); }

            bool operator==(Iterator rhs) { return (mNode == rhs.mNode); }
            bool operator!=(Iterator rhs) { return (mNode != rhs.mNode); }

            void operator=(Iterator rhs) { mNode = rhs.mNode; }
            void operator=(Node *rhs) { mNode = node; }
        private:
            Node *mNode;
        };

        inline Node * GetNode(T *elem) { return (Node *)((char *)elem - ofs); }

        Iterator& Begin() { return Iterator(mHead); }
        Iterator& End() { return Iterator(mTail); }

        u32 Size() const { return mSize; }
        bool IsEmpty() const { return (mSize == 0); }
        
        void Prepend(T *obj)
        {
            CADDIE_ASSERT(obj != NULL);
            Insert(Begin(), GetNode(obj));
        }

        void Append(T *obj)
        {
            CADDIE_ASSERT(obj != NULL);
            Insert(End(), GetNode(obj));
        }     
    private:
        void Insert(Iterator, Node *);

        Node *mHead;
        Node *mTail;
        u32 mSize;
    };
}

#endif