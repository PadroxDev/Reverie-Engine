#include <numbers>

#pragma once

namespace ReverieEngine::Math
{
    // Constants for mathematical calculations
    static constexpr float E = std::numbers::e_v<float>;
    static constexpr float PI = std::numbers::pi_v<float>;
    static constexpr float TWO_PI = 2.0f * PI;
    static constexpr float HALF_PI = 0.5f * PI;
    static constexpr float INV_PI = 1.0f / PI;
    static constexpr float INV_TWO_PI = 1.0f / TWO_PI;
    static constexpr float INV_HALF_PI = 1.0f / HALF_PI;
    static constexpr float SQRT2 = std::numbers::sqrt2_v<float>;
    static constexpr float LOG2E = std::numbers::log2e_v<float>;
    static constexpr float LOG10E = std::numbers::log10e_v<float>;
    static constexpr float PHI = std::numbers::phi_v<float>;
    static constexpr float DEG2RAD = PI / 180.0f;
    static constexpr float RAD2DEG = 180.0f / PI;
    static constexpr float EPSILON = std::numeric_limits<float>::epsilon();
    static constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
    static constexpr float MIN_FLOAT = std::numeric_limits<float>::lowest();
    static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
    static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
    static constexpr float FLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
}
