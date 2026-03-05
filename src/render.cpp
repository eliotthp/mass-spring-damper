#include "render.hpp"
#include <iostream>
#include <cmath>

std::string render(const State &state, const Config &cfg)
{
    State clamped_state = state;
    clamped_state.position = std::max(cfg.x_min, std::min(cfg.x_max, state.position));

    double alpha = (clamped_state.position - cfg.x_min) / (cfg.x_max - cfg.x_min);
    int col = round(alpha * (cfg.width - 1));

    for (int i = 0; i < cfg.width; ++i)
    {
        if (i == col)
            std::cout << "o";
        else
            std::cout << "-";
    }

    return "line";
}