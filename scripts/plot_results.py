import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

if len(sys.argv) > 1:
    output_file = sys.argv[1]
else:
    output_file = "simulation_data.csv"

csv_path = os.path.join(os.path.dirname(__file__), "..", "data", output_file)

data = pd.read_csv(csv_path)

plt.figure(figsize=(10, 5))
plt.plot(data["Time"], data["Position"], label="Position (m)")
plt.xlabel("Time (s)")
plt.ylabel("Position (m)")
plt.title("Mass-Spring-Damper Simulation Results")
plt.legend()
plt.grid(True)
plt.show()
