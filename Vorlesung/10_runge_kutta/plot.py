import matplotlib.pyplot as plt

with open('output','r') as f: 
    values = [[float(v) for v in l.strip().split(" ")] for l in f]

valt = [val[0] for val in values] 
valx = [val[1] for val in values] 
valy = [val[2] for val in values] 

ax,fig = plt.subplots()
plt.xlabel('t')
plt.ylabel('x,y')
plt.plot(valt,valx,'-',label='x')
plt.plot(valt,valy,'-',label='y')
plt.legend()
plt.show()

