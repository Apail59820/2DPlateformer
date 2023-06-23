#pragma once

namespace utils
{
    inline float Lerp(float x, float y, float z) noexcept {
        return ((1.0f - z) * x) + (z * y);
    }
}