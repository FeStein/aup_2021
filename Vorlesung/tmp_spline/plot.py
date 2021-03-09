import matplotlib.pyplot as plt

with open('spline.dat','r') as f: lines = [[float(i) for i in l.strip().split()] for l in f]
with open('xy_data.dat','r') as f: values = [[float(i) for i in l.strip().split()] for l in f]

x = [l[0] for l in lines]
y = [l[1] for l in lines]

xdat = [l[0] for l in values]
ydat = [l[1] for l in values]

fig,ax = plt.subplots()
plt.plot(x,y,c='b')
plt.plot(xdat,ydat,'.',c='r')
plt.show()


