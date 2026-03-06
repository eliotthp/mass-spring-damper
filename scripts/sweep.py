import sys
import os
import subprocess
import itertools

PYTHON = sys.executable
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.join(SCRIPT_DIR, "..")
SIM_PATH = os.path.join(PROJECT_ROOT, "build", "sim")

kps = [10, 20, 30]
kds = [2, 5, 10]
kis = [1, 5]

filenames = []

for kp, kd, ki in itertools.product(kps, kds, kis):
    filename = f"kp{kp}_kd{kd}_ki{ki}.csv"
    subprocess.run(
        [
            SIM_PATH,
            "--kp",
            str(kp),
            "--kd",
            str(kd),
            "--ki",
            str(ki),
            "--output",
            filename,
        ],
        check=True,
    )
    filenames.append(filename)

subprocess.run(
    [PYTHON, os.path.join(SCRIPT_DIR, "plot_results.py"), *filenames], check=True
)
