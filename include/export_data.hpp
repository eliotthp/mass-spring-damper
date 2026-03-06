#pragma once

#include <vector>
#include <string>
#include "plant.hpp"

struct Sample
{
    double time;
    double position;
    double velocity;
    double error;
    double input_force;
};

// Writes simulation state history to a CSV file for plotting
int exportData(const std::vector<Sample> &sample_history, const std::string &output_file);