#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>

#include "plant.hpp"
#include "export_data.hpp"

using namespace std;

struct PIDController
{
    double kp; // Proportional gain
    double ki; // Integral gain
    double kd; // Derivative gain
};

int main(int argc, char **argv)
{
    double x0 = 0.0;                            // Default initial position (m).
    double k = 5.0;                             // Default spring constant (N/m).
    double c = 0.5;                             // Default damping coefficient (N*s/m).
    double sp = 1.0;                            // Default setpoint for control (m).
    double kp = 1.0;                            // Default proportional gain for control (N/m).
    double ki = 1.0;                            // Default integral gain for control (N*s/m).
    double kd = 1.0;                            // Default derivative gain for control (N*s/m).
    string output_file = "simulation_data.csv"; // Default output file for CSV data.
    // Parse CLI args
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "--help")
        {
            cout << "Usage: " << argv[0] << " [--output <output_file>] [--x0 <initial_position>] [--k <spring_constant>] [--c <damping_coefficient>] [--sp <setpoint>] [--kp <proportional_gain>] [--ki <integral_gain>] [--kd <derivative_gain>]" << endl;
            return 0;
        }
        else if (arg == "--output")
        {
            output_file = argv[++i];
        }
        else if (arg == "--x0")
        {
            x0 = stod(argv[++i]);
        }
        else if (arg == "--k")
        {
            k = stod(argv[++i]);
        }
        else if (arg == "--c")
        {
            c = stod(argv[++i]);
        }
        else if (arg == "--sp")
        {
            sp = stod(argv[++i]);
        }
        else if (arg == "--kp")
        {
            kp = stod(argv[++i]);
        }
        else if (arg == "--ki")
        {
            ki = stod(argv[++i]);
        }
        else if (arg == "--kd")
        {
            kd = stod(argv[++i]);
        }
    }

    MassSpringDamper plant(1.0, k, c);

    // Initial condition: displaced left with zero initial velocity.
    State state{0.0, x0, 0.0};
    PIDController controller{kp, ki, kd};

    vector<Sample> sample_history;
    sample_history.push_back({state.time, state.position, state.velocity, 0.0, 0.0});

    double dt = 0.01;
    double error;
    double error_sum = 0.0;
    double input_force;

    // Run simulation for 20 seconds
    for (int i = 0; i < 2000; ++i)
    {
        error = sp - state.position;
        error_sum += error * dt;
        input_force = controller.kp * error + controller.ki * error_sum + controller.kd * (-state.velocity); // PID control
        state = plant.step(state, input_force, dt);
        sample_history.push_back({state.time, state.position, state.velocity, error, input_force});
    }

    exportData(sample_history, output_file);

    // Successful exit.
    return 0;
}