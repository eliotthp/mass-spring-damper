#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "plant.hpp"
#include "export_data.hpp"

using namespace std;

int exportData(const std::vector<State> &states_history, const std::string &output_file)
{
    if (filesystem::exists("../data"))
    {
        cout << "Exporting " + output_file + "\n";
    }
    else if (!filesystem::exists("../data"))
    {
        cout << "Creating data directory...\n";
        filesystem::create_directory("../data");
    }
    ofstream outFile("../data/" + output_file);

    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing!\n";
        return -1;
    }

    outFile << "Time,Position,Velocity\n";
    for (const auto &state : states_history)
    {
        outFile << state.time << "," << state.position << "," << state.velocity << "\n";
    }

    return 0;
}