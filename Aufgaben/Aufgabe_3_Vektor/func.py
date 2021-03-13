import numpy as np
import matplotlib.pyplot as plt

X = np.linspace(0, 1, 1001)
Y = - np.tan( np.pi * X - np.pi / 2)

Y[0] = 5

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

X = np.concatenate(([0],X))
Y = np.concatenate(([0],Y))

X_final = np.concatenate((X,X+1,X+2,[3]))
Y_final = np.concatenate((Y,Y,Y,[0]))

#plt.plot(X_final, Y_final)
#plt.ylim(-20,20)
#plt.xlim(0,3)
#plt.show()

with open("signal.dat", "w+") as file:
    for line in range(X_final.size):
        file.write(f"{X_final[line]} {Y_final[line]}\n")
