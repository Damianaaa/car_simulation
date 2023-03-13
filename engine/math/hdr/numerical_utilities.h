#ifndef ENGINE_MATH_HDR_NUMERICAL_UTILITIES_H
#define ENGINE_MATH_HDR_NUMERICAL_UTILITIES_H

namespace math
{

constexpr bool fEqual(const float f1, const float f2)
{
    constexpr float precision{0.001};
    return (f1 - f2) > 0 ? (f1 - f2) < precision : (f2 - f1) < precision;
}

constexpr bool fLEqual(const float f1, const float f2)
{
    return f2 > f1 || fEqual(f1, f2);
}

constexpr bool fGEqual(const float f1, const float f2)
{
    return f1 > f2 || fEqual(f1, f2);
}

}  // math

#endif  // ENGINE_MATH_HDR_NUMERICAL_UTILITIES_H