import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("output", names=["T", "X", "V"])

plt.plot(df["T"], df["X"], label="$x$")
plt.plot(df["T"], df["V"], label="$v$")


plt.legend()
plt.show()
