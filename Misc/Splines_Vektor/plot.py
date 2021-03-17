import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("output",names=["X","Y"])

plt.plot(df["X"], df["Y"])
plt.show()
