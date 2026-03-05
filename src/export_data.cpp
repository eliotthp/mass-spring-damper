#include <iostream>
#include <fstream>
#include <vector>
#include "plant.hpp"
#include "export_data.hpp"

int exportData(const std::vector<State> &states_history)
{
    std::ofstream outFile("../data/simulation_data.csv");
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing!\n";
        return -1;
    }

    outFile << "Time,Position,Velocity\n";
    for (const auto &state : states_history)
    {
        outFile << state.time << "," << state.position << "," << state.velocity << "\n";
    }

    return 0;
}