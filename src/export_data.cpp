#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "plant.hpp"
#include "export_data.hpp"

using namespace std;

int exportData(const vector<Sample> &sample_history, const string &output_file)
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

    outFile << "Time,Position,Velocity,Error,Input Force\n";
    for (const auto &sample : sample_history)
    {
        outFile << sample.time << "," << sample.position << "," << sample.velocity << "," << sample.error << "," << sample.input_force << "\n";
    }

    return 0;
}