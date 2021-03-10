import numpy as np

with open('log.dat','r') as f: lines = [float(l.strip()) for l in f]
R = np.array([14.848, 10.3992, 5.99526, 3.93177, 2.7882])
M = np.array(lines).reshape(5,5)

print(M)

def jacobi(A,b,N=25,x=None):
    """Solves the equation Ax=b via the Jacobi iterative method."""
    # Create an initial guess if needed                                                                                                                                                            
    if x is None:
        x = zeros(len(A[0]))
    
    # Create a vector of the diagonal elements of A                                                                                                                                                
    # and subtract them from A                                                                                                                                                                     
    D = diag(A)
    R = A - diagflat(D)
    
    # Iterate for N times                                                                                                                                                                          
    for i in range(N):
        x = (b - dot(R,x)) / D
    return x

X = np.linalg.solve(M,R)
X2 = np.linalg.solve(M,R)
print(X)
print(X2)
