import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def plot_results(output_file):
    csv_path = os.path.join(os.path.dirname(__file__), "..", "data", output_file)
    data = pd.read_csv(csv_path)
    plt.plot(data["Time"], data["Position"], label=output_file)

def main():
    output_files = []

    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            output_files.append(arg)
    else:
        output_files.append("simulation_data.csv")

    plt.figure(figsize=(10, 6))

    for output_file in output_files:
        plot_results(output_file)

    plt.xlabel("Time (s)")
    plt.ylabel("Position (m)")
    plt.title("Mass-Spring-Damper Simulation Results")
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()