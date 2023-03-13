#ifndef NW4R_UT_LINK_LIST_H
#define NW4R_UT_LINK_LIST_H
#include "ut_NonCopyable.h"

#include <types_nw4r.h>

// Create typedef for templated LinkList structure
#define NW4R_UT_LINKLIST_TYPEDEF(T, NAME)                                      \
    typedef nw4r::ut::LinkList<T, offsetof(T, mNode)> NAME

// Create typedef for templated LinkList structure
#define NW4R_UT_LINKLIST_TYPEDEF_EX(T, T_INNER, NAME)                          \
    typedef nw4r::ut::LinkList<T, offsetof(T_INNER, mNode)> NAME

namespace nw4r {
namespace ut {

class LinkListNode : public NonCopyable {
    friend class detail::LinkListImpl;

public:
    LinkListNode() : mNext(NULL), mPrev(NULL) {}

    LinkListNode* GetNext() const { return mNext; }
    LinkListNode* GetPrev() const { return mPrev; }

private:
    LinkListNode* mNext; // at 0x0
    LinkListNode* mPrev; // at 0x4
};

namespace detail {

class LinkListImpl : public NonCopyable {
public:
    struct Iterator {
        Iterator(LinkListNode* node) : mNode(node) {}

        Iterator& operator++() {
            mNode = mNode->GetNext();
            return *this;
        }

        Iterator& operator--() {
            mNode = mNode->GetPrev();
            return *this;
        }

        LinkListNode* operator->() const { return mNode; }

        bool operator==(LinkListImpl::Iterator other) const {
            return mNode == other.mNode;
        }

        LinkListNode* mNode; // at 0x0
    };

    struct ConstIterator : public Iterator {
        ConstIterator(LinkListNode* node) : Iterator(node) {}
        ConstIterator(Iterator it) : Iterator(it) {}

        ConstIterator& operator++() {
            mNode = mNode->GetNext();
            return *this;
        }

        ConstIterator& operator--() {
            mNode = mNode->GetPrev();
            return *this;
        }

        const LinkListNode* operator->() const { return mNode; }

        bool operator==(LinkListImpl::ConstIterator other) const {
            return mNode == other.mNode;
        }

        LinkListNode* mNode; // at 0x0
    };

public:
    static Iterator GetIteratorFromPointer(LinkListNode* node) {
        return Iterator(node);
    }

    LinkListImpl() { Initialize_(); }
    ~LinkListImpl();

    Iterator GetBeginIter() { return Iterator(mNode.GetNext()); }
    Iterator GetEndIter() { return Iterator(&mNode); }

    u32 GetSize() const { return mSize; }
    bool IsEmpty() const { return mSize == 0; }

    void PopFront() { Erase(GetBeginIter()); }
    void PopBack() { Erase(GetEndIter()); }

    Iterator Insert(Iterator it, LinkListNode* node);

    Iterator Erase(Iterator it);
    Iterator Erase(LinkListNode* node);
    Iterator Erase(Iterator begin, Iterator end);

    void Clear();

private:
    void Initialize_() {
        mSize = 0;
        mNode.mNext = &mNode;
        mNode.mPrev = &mNode;
    }

private:
    u32 mSize;          // at 0x0
    LinkListNode mNode; // at 0x4
};

} // namespace detail

template <typename T, int Ofs> class LinkList : public detail::LinkListImpl {
public:
    struct Iterator {
        Iterator(LinkListImpl::Iterator it) : mIterator(it) {}

        Iterator& operator++() {
            mIterator.operator++();
            return *this;
        }

        Iterator& operator--() {
            mIterator.operator--;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret = *this;
            ++*this;
            return ret;
        }

        T* operator->() const {
            return GetPointerFromNode(mIterator.operator->());
        }

        T& operator*() const { return *this->operator->(); }

        bool operator==(Iterator other) const {
            return mIterator == other.mIterator;
        }

        bool operator!=(Iterator other) const {
            return (*this == other) == false;
        }

        LinkListImpl::Iterator mIterator; // at 0x0
    };

    struct ConstIterator : public Iterator {
        ConstIterator(LinkListImpl::Iterator it) : Iterator(it) {}
        ConstIterator(LinkListImpl::ConstIterator it) : Iterator(it) {}

        ConstIterator& operator++() {
            mIterator.operator++();
            return *this;
        }

        ConstIterator& operator--() {
            mIterator.operator--;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator ret = *this;
            ++*this;
            return ret;
        }

        const T* operator->() const {
            return GetPointerFromNode(mIterator.operator->());
        }

        const T& operator*() const { return *this->operator->(); }

        bool operator==(ConstIterator other) {
            return mIterator == other.mIterator;
        }

        bool operator!=(ConstIterator other) {
            return (*this == other) == false;
        }

        LinkListImpl::ConstIterator mIterator; // at 0x0
    };

public:
    LinkList() {}
    ~LinkList() {}

    Iterator GetBeginIter() { return Iterator(LinkListImpl::GetBeginIter()); }
    ConstIterator GetBeginIter() const { return ConstIterator(GetBeginIter()); }

    Iterator GetEndIter() { return Iterator(LinkListImpl::GetEndIter()); }
    ConstIterator GetEndIter() const { return ConstIterator(GetEndIter()); }

    Iterator Insert(Iterator it, T* p) {
        return Iterator(
            LinkListImpl::Insert(it.mIterator, GetNodeFromPointer(p)));
    }

    Iterator Erase(T* p) {
        return Iterator(LinkListImpl::Erase(GetNodeFromPointer(p)));
    }

    Iterator Erase(Iterator it) {
        return Iterator(LinkListImpl::Erase(it.mIterator));
    }

    void PushBack(T* p) { Insert(GetEndIter(), p); }

    T& GetBack() { return *--GetEndIter(); }
    const T& GetBack() const { return *--GetEndIter(); }

    static LinkListNode* GetNodeFromPointer(T* p) {
        return reinterpret_cast<LinkListNode*>(reinterpret_cast<char*>(p) +
                                               Ofs);
    }

    static T* GetPointerFromNode(LinkListNode* node) {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(node) - Ofs);
    }

    static const T* GetPointerFromNode(const LinkListNode* node) {
        return reinterpret_cast<const T*>(reinterpret_cast<const char*>(node) -
                                          Ofs);
    }
};

} // namespace ut
} // namespace nw4r

#endif
