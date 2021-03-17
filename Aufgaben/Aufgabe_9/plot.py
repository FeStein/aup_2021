import matplotlib.pyplot as plt

with open('output','r') as f: lines = [l.strip() for l in f]

splitted = [[float(s) for s in l.split(" ")] for l in lines]

y = [s[0] for s in splitted]
u = [-s[1] for s in splitted]

ax,fig = plt.subplots()
plt.ylabel('y')
plt.xlabel('u(y)')
plt.plot(u,y,'-',label='impl. Differenzenverfahren')
plt.legend()
plt.ylim(0,1)
plt.show()

