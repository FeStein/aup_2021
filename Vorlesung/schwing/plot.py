import sys,os
import matplotlib.pyplot as plt
import tikzplotlib
import argparse                                                                                                                                          
                                                                                                                                                           
ap = argparse.ArgumentParser()                                                                                                                           
ap.add_argument("-f", "--filename", required=False, type=str, default='.',                                                                                         
                help="path to file")                                                                                                                     
                                                                                                                                                          
args = vars(ap.parse_args())                                                                                                                             
filename = args["filename"] 

with open(filename,'r') as f: lines = [l.split(',') for l in f]

t_val= [float(l[0].strip()) for l in lines]
x_val= [float(l[1].strip()) for l in lines]
y_val= [float(l[2].strip()) for l in lines]

ax,fig = plt.subplots()
plt.xlabel('x axis')
plt.ylabel('y axis')
plt.plot(t_val,x_val,'-',label='plot')
plt.plot(t_val,y_val,'-',label='plot')
#plt.legend()
#plt.xlim(1,1)
#plt.ylim(1,1)
#tikzplotlib.save('fig.tex')
plt.show()


