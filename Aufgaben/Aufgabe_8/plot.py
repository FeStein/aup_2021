import pandas as pd
import matplotlib.pyplot as plt
import os

output_files = sorted([f for f in os.listdir() if f.startswith("output")], key = lambda x: float(x.split("_")[1]))

for on in output_files:
    ts_name = on.split("_")[1]
    df = pd.read_csv(on, names=["X","T"])
    plt.plot(df["X"],df["T"], label = ts_name)


plt.legend()
plt.show()
