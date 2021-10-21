#ifndef NW4R_UT_ALGORITHM_H
#define NW4R_UT_ALGORITHM_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		namespace
		{
			template <typename T>
			inline T Clamp(T min, T max, T value)
			{
				if (max < value) return max;
				return (value < min) ? min : value;
			}
		}
	}
}

#endif