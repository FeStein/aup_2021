import matplotlib.pyplot as plt

with open('output','r') as f: 
    values = [[float(v) for v in l.strip().split(" ")] for l in f]

valt = [val[0] for val in values] 
valx = [val[1] for val in values] 
valz = [val[2] for val in values] 
valxp = [val[3] for val in values] 
valzp = [val[4] for val in values] 

ax,fig = plt.subplots()
plt.xlabel('x')
plt.ylabel('z')
plt.plot(valx,valz,'-',label='Flugkurve')
plt.plot(valx,valxp,'-',label='v_x')
plt.plot(valx,valzp,'-',label='v_z')
plt.legend()
plt.show()

