import sys
import subprocess
import itertools

PYTHON = sys.executable

kps = [5, 10, 20]
kds = [0, 2, 5]
kis = [0, 1]

filenames = []

for kp, kd, ki in itertools.product(kps, kds, kis):
    filename = f"kp{kp}_kd{kd}_ki{ki}.csv"
    subprocess.run(["../build/sim", "--kp", str(kp), "--kd", str(kd), "--ki", str(ki), "--output", filename], check=True)
    filenames.append(filename)

subprocess.run([PYTHON, "../scripts/plot_results.py", *filenames], check=True)