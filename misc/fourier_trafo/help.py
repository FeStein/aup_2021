import matplotlib.pyplot as plt
import sys
from math import sin,cos,pi

#define input function
m = 1001   #must be the same as in cpp file     
T = 2      #must be the same as in cpp file 

f = lambda x : x**2 
f = lambda x : 7*sin(x*((2*pi)/T)) + 4*cos(x*((2*pi)/T))
f = lambda x : 1 if x > T/2 else 0

#make input.dat
if sys.argv[1] == "0":
    x_val = [(x/m)*T for x in range(m)]
    y_val = [f(x) for x in x_val]

    with open('input.dat','w+') as f:
        for x,y in zip(x_val,y_val): f.write(str(x) + " " + str(y) + "\n")

#plotting after stuff is done
if sys.argv[1] == "1":
    with open('approx.dat','r') as f: lines = [l.split() for l in f]

    x_val = [float(l[0]) for l in lines]
    fun = [float(l[1]) for l in lines]
    approx = [float(l[2]) for l in lines]

    plt.plot(x_val,fun,'-',label='function')
    plt.plot(x_val,approx,'-',label='approx',alpha=0.8)
    plt.legend()
    plt.show()


