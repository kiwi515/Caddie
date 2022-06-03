#ifndef CADDIE_MATH_ALGORITHM_H
#define CADDIE_MATH_ALGORITHM_H
#include "types_caddie.h"

namespace caddie
{
    template <typename T>
    inline const T Max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }

    template <typename T>
    inline const T Min(const T& a, const T& b)
    {
        return (b < a) ? b : a;
    }
}

#endif