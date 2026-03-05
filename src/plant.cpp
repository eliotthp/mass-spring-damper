#include "plant.hpp"

MassSpringDamper::MassSpringDamper(double mass, double spring_constant, double damping_coefficient)
    : m_(mass), k_(spring_constant), c_(damping_coefficient) {}

State MassSpringDamper::step(const State &current_state, double input_force, double dt)
{
    const double dx = current_state.velocity;
    const double dv = (input_force - k_ * current_state.position - c_ * current_state.velocity) / m_;

    return State{
        current_state.time + dt,
        current_state.position + dx * dt,
        current_state.velocity + dv * dt};
}