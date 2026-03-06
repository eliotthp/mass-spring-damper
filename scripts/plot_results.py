import pandas as pd
import matplotlib.pyplot as plt
import sys
import os
import csv

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.join(SCRIPT_DIR, "..")


def plot_position_results(output_file):
    csv_path = os.path.join(PROJECT_ROOT, "data", output_file)
    data = pd.read_csv(csv_path)
    plt.plot(data["Time"], data["Position"], label=output_file)


def plot_input_forces_results(output_file):
    csv_path = os.path.join(PROJECT_ROOT, "data", output_file)
    data = pd.read_csv(csv_path)
    plt.plot(data["Time"], data["Input Force"], label=output_file)


def compute_response_metrics(output_file):
    csv_path = os.path.join(PROJECT_ROOT, "data", output_file)
    data = pd.read_csv(csv_path)
    sp = data["Setpoint"].iloc[0]
    # Compute overshoot
    overshoot = (data["Position"].max() - sp) / sp
    # Compute settling time
    # Find list of true/false
    settling_cond_list = data["Position"].between(sp * 0.95, sp * 1.05)
    # Find last index where false, then add 1 to get first index where true
    last_false = -1
    for i in range(len(data) - 1, -1, -1):
        if not settling_cond_list[i]:
            last_false = i
            break
    start_index = last_false + 1
    settling_time = data["Time"].iloc[start_index]
    # Compute steady-state error
    steady_state_error = abs(
        data["Position"].iloc[-1] - sp
    )  # Final error from setpoint

    return overshoot, settling_time, steady_state_error


def rank_results(output_files):
    results = []

    for output_file in output_files:
        overshoot, settling_time, steady_state_error = compute_response_metrics(
            output_file
        )
        # Compute cost
        J = (
            (10 * overshoot) ** 2
            + (settling_time) ** 2
            + (50 * steady_state_error) ** 2
        )
        results.append((output_file, J, overshoot, settling_time, steady_state_error))

    results.sort(key=lambda x: x[1])  # Sort by cost

    with open(os.path.join(PROJECT_ROOT, "results.csv"), "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(
            [
                "Output File",
                "Cost J",
                "Overshoot",
                "Settling Time (s)",
                "Steady-State Error",
            ]
        )
        for result in results:
            writer.writerow(result)


def main():
    output_files = []

    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            output_files.append(arg)
    else:
        output_files.append("simulation_data.csv")

    rank_results(output_files)

    csv_path = os.path.join(PROJECT_ROOT, "results.csv")
    data = pd.read_csv(csv_path)

    numBest = 20
    best = data["Output File"].head(numBest)
    output_files = best.tolist()

    plt.figure(figsize=(12, 6))

    for output_file in output_files:
        plot_position_results(output_file)

    plt.xlabel("Time (s)")
    plt.ylabel("Position (m)")
    plt.title("Mass-Spring-Damper Simulation Results")
    plt.legend(bbox_to_anchor=(1, 1), loc="upper left")
    plt.grid(True)
    plt.subplots_adjust(left=0.067, right=0.8)
    plt.show()

    plt.figure(figsize=(12, 6))

    for output_file in output_files:
        plot_input_forces_results(output_file)

    plt.xlabel("Time (s)")
    plt.ylabel("Input Force (N)")
    plt.title("Input Force Over Time")
    plt.legend(bbox_to_anchor=(1, 1), loc="upper left")
    plt.grid(True)
    plt.subplots_adjust(left=0.067, right=0.8)
    plt.show()


if __name__ == "__main__":
    main()
