#pragma once
#include <array>

struct window_config {
    int width;
    int height;
    std::array<float, 2> multiplier;
    const char *window_name;
};