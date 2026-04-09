#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "plant.hpp"
#include "export_data.hpp"

using namespace std;

int exportData(const vector<Sample> &sample_history, const string &output_file)
{
    const filesystem::path data_dir = filesystem::path(PROJECT_ROOT_DIR) / "data";

    if (filesystem::exists(data_dir))
    {
        cout << "Exporting " + output_file + "\n";
    }
    else
    {
        cout << "Creating data directory...\n";
        filesystem::create_directories(data_dir);
    }
    ofstream outFile(data_dir / output_file);

    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing!\n";
        return -1;
    }

    outFile << "Time,Position,Velocity,Error,Input Force,Setpoint\n";
    for (const auto &sample : sample_history)
    {
        outFile << sample.time << "," << sample.position << "," << sample.velocity << "," << sample.error << "," << sample.input_force << "," << sample.setpoint << "\n";
    }

    return 0;
}