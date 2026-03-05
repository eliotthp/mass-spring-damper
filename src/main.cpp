#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "plant.hpp"
#include "export_data.hpp"
#include "render.hpp"

using namespace std;

struct PIDController
{
    double kp; // Proportional gain
    double kd; // Derivative gain
};

int main(int argc, char **argv)
{
    double x0 = -1.0; // Default initial position (m).
    double k = 5.0;   // Default spring constant (N/m).
    double c = 0.7;   // Default damping coefficient (N*s/m).
    double sp = 0.0;  // Default setpoint for control (m).
    double kp = 0.0;  // Default proportional gain for control (N/m).
    double kd = 0.0;  // Default derivative gain for control (N*s/m).
    // Parse CLI args
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "--help")
        {
            cout << "Usage: " << argv[0] << " [--x0 <initial_position>] [--k <spring_constant>] [--c <damping_coefficient>] [--sp <setpoint>] [--kp <proportional_gain>] [--kd <derivative_gain>]" << endl;
            return 0;
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
        else if (arg == "--kd")
        {
            kd = stod(argv[++i]);
        }
    }

    MassSpringDamper plant(1.0, k, c);

    // Initial condition: displaced left with zero initial velocity.
    State state{0.0, x0, 0.0};
    PIDController controller{kp, kd};

    vector<State> states_history;
    states_history.push_back(state);

    double error = sp - state.position;
    double input_force = controller.kp * error + controller.kd * (-state.velocity); // PD control
    // Fixed integration step for simulation (s).
    double dt = 0.01;

    // Run simulation for 1000 integration steps.
    for (int i = 0; i < 1000; ++i)
    {
        error = sp - state.position;
        input_force = controller.kp * error + controller.kd * (-state.velocity); // Proportional control
        state = plant.step(state, input_force, dt);
        states_history.push_back(state);
    }

    exportData(states_history);

    // Successful exit.
    return 0;
}