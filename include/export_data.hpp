#pragma once

#include <vector>
#include <string>
#include "plant.hpp"

// Writes simulation state history to a CSV file for plotting
int exportData(const std::vector<State> &states_history, const std::string &output_file);