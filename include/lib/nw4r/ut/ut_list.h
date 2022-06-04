#ifndef NW4R_UT_LIST
#define NW4R_UT_LIST
#include "types_nw4r.h"

#define UT_LIST_FOREACH(list, type, name) \
	type *name = NULL; \
	while (name = (type *)nw4r::ut::List_GetNext(list, name))

namespace nw4r
{
	namespace ut
	{
		struct List
		{
			void *mHead;
			void *mTail;
			u16 mSize;
			u16 mOffset;
		};

		struct Node
		{
			void *mPrev;
			void *mNext;
		};

		void List_Init(List *, u16);
		void List_Append(List *, void *);
		void List_Insert(List *, void *, void *);
		void List_Remove(List *, void *);
		void * List_GetNext(const List *, const void *);
		void * List_GetPrev(const List *, const void *);
		void * List_GetNth(const List *, u16);

		inline void * List_GetFirst(const List * list)
		{
			return List_GetNext(list, NULL);
		}
	}
}

#endif
