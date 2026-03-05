# Mass-Spring-Damper Control Simulation

## Description
C++ simulation of a mass-spring-damper (MSD) system with PID control. Python is used for visualization and parameter sweeps.

This project was built to learn C++, CMake, WSL, and Python integration.

## Features
- PID controller implementation
- CLI parameter tuning
- CSV export
- Python plotting
- Automated gain sweeps

### Example Usage
```bash
./sim --sp 1 --kp 10 --kd 5 --ki 1 --output run.csv
```
### Run Sweep
```bash
python scripts/sweep.py
```
### Plot Results
```bash
python scripts/plot_results.py file1.csv file2.csv
```
