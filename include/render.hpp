#pragma once
#include <string>
#include "plant.hpp"

struct Config
{
    int width;
    double x_min;
    double x_max;
};

std::string render(const State &state, const Config &cfg);