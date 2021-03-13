import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("output", names=["X","T"])

plt.plot(df["X"],df["T"])

plt.show()
