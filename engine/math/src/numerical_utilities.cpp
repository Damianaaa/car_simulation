#include "engine/math/hdr/numerical_utilities.h"
#include <math.h>
#include <limits>

namespace math
{
constexpr float precision{0.001};

bool fEqual(const float f1, const float f2)
{
    return std::fabs(f1 - f2) < precision;
}

bool fLEqual(const float f1, const float f2)
{
    return f2 > f1 || fEqual(f1, f2);
}

bool fGEqual(const float f1, const float f2)
{
    return f1 > f2 || fEqual(f1, f2);

}

}  // math
