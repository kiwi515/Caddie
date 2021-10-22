#include "caddieTLinkList.h"

namespace caddie
{
    template <typename T, int ofs>
    void TLinkList<T, ofs>::Insert(Iterator it, Node *node)
    {
        CADDIE_ASSERT(node != NULL);
        
        Node *after = it.mNode;
        Node *before = after->mPrev;
        CADDIE_ASSERT_EX(before != NULL, "List is broken!!!\n");

        before->mNext = node;
        node->mPrev = before;
        after->mPrev = node;
        node->mNext = after;

        mSize++;
    }
}