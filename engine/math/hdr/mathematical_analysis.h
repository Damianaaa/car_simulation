#ifndef ENGINE_MATH_HDR_MATHEMATICAL_ANALYSIS_H
#define ENGINE_MATH_HDR_MATHEMATICAL_ANALYSIS_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>

namespace math
{
    float calculateDelta(const float coeff_a, const float coeff_b, const float coeff_c)
    {
        return pow(coeff_b, 2) - (4 * coeff_a * coeff_c); 
    }

    std::vector<float> getQuadraticEquationSolutions(const float coeff_a, const float coeff_b, const float coeff_c)
    {
        const float delta{calculateDelta(coeff_a, coeff_b, coeff_c)};
        if (delta < 0)
            return {};
        else if (delta == 0)
            return {(-coeff_b) / (2 * coeff_a)};
        else
        {
            const float delta_sqr = sqrt(delta);
            const float x1 = (-coeff_b + delta_sqr) / (2 * coeff_a);
            const float x2 = (-coeff_b - delta_sqr) / (2 * coeff_a);
            return {x1, x2};
        }
    }

}  // math

#endif
