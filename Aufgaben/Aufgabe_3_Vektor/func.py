import numpy as np
import matplotlib.pyplot as plt

X = np.linspace(0, 2, 1000)
Y = - np.tan( np.pi * X - np.pi / 2)

border = 15
check = False
for index in range(X.size):
    if Y[index] > border:
        check = True
    if Y[index] < border and check:
        break
X = X[index:]
Y = Y[index:]

for index in range(X.size):
    if Y[index] < -border:
        break

X = X[:index - 1]
Y = Y[:index - 1]

X_final = np.append(X, X + X[-1])
Y_final = np.append(Y, Y)

X_final = np.append(X_final, X + X_final[-1])
Y_final = np.append(Y_final, Y)

plt.plot(X_final, Y_final)
plt.ylim(-20,20)
plt.show()

#with open("signal.dat", "w+") as file:
#    for line in range(X_final.size):
#        file.write(f"{X_final[line]}\t{Y_final[line]}\n")
