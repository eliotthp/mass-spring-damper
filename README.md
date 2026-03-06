# Mass-Spring-Damper PID Control Sandbox

A C++ simulation of a 1D mass-spring-damper system with PID control and anti-windup. Python scripts handle visualization and automated parameter sweeps to find optimal gains.

## System Model

The plant simulates a mass-spring-damper governed by:

$$m\ddot{x} + c\dot{x} + kx = F$$

where $m$ is mass, $c$ is damping coefficient, $k$ is spring constant, and $F$ is the applied control force. Integration uses the 4th-order Runge-Kutta (RK4) method with a 0.01s timestep over a 10-second window.

## PID Controller

The controller computes the input force as:

$$F = k_p \, e + k_i \int e \, dt + k_d (-\dot{x})$$

where $e = x_{sp} - x$ is the position error. Output is clamped to [0, 10] N with integral anti-windup (accumulated error is unwound when the output saturates).

## Project Structure

```
├── CMakeLists.txt          # Build system (C++17, CMake 3.16+)
├── include/
│   ├── plant.hpp           # MassSpringDamper class and State struct
│   └── export_data.hpp     # Sample struct and CSV export function
├── src/
│   ├── main.cpp            # Simulation entry point, PID logic, CLI parsing
│   ├── plant.cpp           # RK4 integration and system dynamics
│   └── export_data.cpp     # CSV writer
├── scripts/
│   ├── plot_results.py     # Plot position/force, compute response metrics, rank results
│   └── sweep.py            # Automated parameter sweep over kp/kd/ki ranges
└── data/                   # Output CSV files
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Run a single simulation

```bash
./build/sim --sp 1 --kp 20 --kd 3 --ki 5
```

Results are written to `data/simulation_data.csv`.

### CLI Options

| Flag       | Description              | Default |
|------------|--------------------------|---------|
| `--x0`     | Initial position (m)     | 0.0     |
| `--k`      | Spring constant (N/m)    | 5.0     |
| `--c`      | Damping coefficient (Ns/m) | 0.5   |
| `--sp`     | Setpoint (m)             | 1.0     |
| `--kp`     | Proportional gain        | 20.0    |
| `--ki`     | Integral gain            | 5.0     |
| `--kd`     | Derivative gain          | 3.0     |
| `--output` | Output CSV filename      | simulation_data.csv |

### Parameter Sweep

Sweeps over a grid of kp, kd, and ki values, runs a simulation for each combination, then ranks and plots the best results:

```bash
python scripts/sweep.py
```

### Plot Results

Plot one or more CSV files. Computes overshoot, settling time (5% band), and steady-state error, then ranks results by a weighted cost function and plots the top 20:

```bash
python scripts/plot_results.py file1.csv file2.csv
```

## Dependencies

- **C++**: CMake 3.16+, C++17 compiler
- **Python**: pandas, matplotlib, numpy
