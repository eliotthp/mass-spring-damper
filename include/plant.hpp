#pragma once

struct State
{
    double time;
    double position;
    double velocity;
};

class MassSpringDamper
{
public:
    MassSpringDamper(double mass, double spring_constant, double damping_coefficient);

    State step(const State &current_state, double input_force, double dt);
    State get_derivatives(const State &current_state, double input_force);
    State rk4(const State &current_state, double input_force, double dt);

private:
    double m_; // Mass
    double k_; // Spring constant
    double c_; // Damping coefficient
};