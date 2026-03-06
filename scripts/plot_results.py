import pandas as pd
import matplotlib.pyplot as plt
import sys
import os


def plot_position_results(output_file):
    csv_path = os.path.join(os.path.dirname(__file__), "..", "data", output_file)
    data = pd.read_csv(csv_path)
    plt.plot(data["Time"], data["Position"], label=output_file)


def plot_input_forces_results(output_file):
    csv_path = os.path.join(os.path.dirname(__file__), "..", "data", output_file)
    data = pd.read_csv(csv_path)
    plt.plot(data["Time"], data["Input Force"], label=output_file)


def main():
    output_files = []

    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            output_files.append(arg)
    else:
        output_files.append("simulation_data.csv")

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
