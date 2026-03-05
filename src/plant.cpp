#include "plant.hpp"

MassSpringDamper::MassSpringDamper(double mass, double spring_constant, double damping_coefficient)
    : m_(mass), k_(spring_constant), c_(damping_coefficient) {}

State MassSpringDamper::step(const State &current_state, double input_force, double dt)
{
    return rk4(current_state, input_force, dt);
}

State MassSpringDamper::get_derivatives(const State &current_state, double input_force)
{
    const double dx = current_state.velocity;
    const double dv = -k_ / m_ * current_state.position - c_ / m_ * current_state.velocity + input_force / m_;

    return State{
        0.0,
        dx,
        dv};
}

State MassSpringDamper::rk4(const State &current_state, double input_force, double dt)
{
    State k1 = get_derivatives(current_state, input_force);
    State k2 = get_derivatives(State{0.0, current_state.position + 0.5 * k1.position * dt, current_state.velocity + 0.5 * k1.velocity * dt}, input_force);
    State k3 = get_derivatives(State{0.0, current_state.position + 0.5 * k2.position * dt, current_state.velocity + 0.5 * k2.velocity * dt}, input_force);
    State k4 = get_derivatives(State{0.0, current_state.position + k3.position * dt, current_state.velocity + k3.velocity * dt}, input_force);

    return State{
        current_state.time + dt,
        current_state.position + (dt / 6.0) * (k1.position + 2.0 * k2.position + 2.0 * k3.position + k4.position),
        current_state.velocity + (dt / 6.0) * (k1.velocity + 2.0 * k2.velocity + 2.0 * k3.velocity + k4.velocity)};
}