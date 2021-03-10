#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

std::vector<double> gauss_seidel(std::vector<std::vector<double>> M, std::vector<double> R);

int main()
{
  double x, y, dx;
  int n,m,diskret;

  // read in the data
  std::vector<double> ARRX;
  std::vector<double> ARRY;
  std::ifstream ifile;
  ifile.open("messpunkte.dat");
  while(ifile >> x >> y){
    ARRX.push_back(x);
    ARRY.push_back(y);
  }
  ifile.close();

  m = ARRX.size(); // number of data points
  n = 5; // polynom size + 1

  // create M + RHS
  std::vector<std::vector<double>> M(n, std::vector<double>(n, 1.0));
  std::vector<double> RHS(n,0.0);

  // fill M + RHS
  for (int i = 0; i < n; ++i) {
    M[0][0] += sqrt(ARRX[i]) * sqrt(ARRX[i]);
    RHS[0] += sqrt(ARRX[i]) * ARRY[i];
  }
  for (int row = 1; row < n; ++row) {
    for (int col = 1; col < n; ++col) {
      for (int i = 0; i < m; ++i) {
        M[row][col] += pow(ARRX[i],col) * pow(ARRX[i],row);
      }
    }
    for (int i = 0; i < m; ++i) {
      // use symmetry
      M[row][0] += pow(ARRX[i],row) * sqrt(ARRX[i]);
      M[0][row] += pow(ARRX[i],row) * sqrt(ARRX[i]);
      RHS[row] += pow(ARRX[i],row) * ARRY[i];
    }
  }

  
  // Solve
  std::cout << "=====solve output=====" << std::endl;

  std::vector<double> ARRA = gauss_seidel(M,RHS);
  
  // output
  diskret = 101; // number of points for output
  dx = (ARRX.back() - ARRX.front()) / (diskret - 1);

  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < diskret; ++i) {
    x = i*dx + ARRX.front();
    y = ARRA[0] * sqrt(x);
    for (int j = 1; j < ARRA.size(); j++) {
      y += ARRA[j] * pow(x,j);
    }
    ofile << x << " " << y << std::endl;
  }

  return 0;
}

std::vector<double> gauss_seidel(std::vector<std::vector<double>> M, std::vector<double> R) {
  int num_iter = 10000;
  int n = R.size();
  std::vector<double> X(n,0.0);

  double sum;

  for (int iter = 0; iter < num_iter; ++iter) {
    for (int row = 0; row < n; ++row) {
      sum = 0.0;
      for (int i = 0; i < row; ++i) {
        if(i != row){
          sum += M[row][i]*X[i];
        }
      }
      X[row] = (1.0/M[row][row]) * (R[row] - sum);
    }    
  }
  for (int i = 0; i < n; ++i) {
    std::cout << X[i] << std::endl; 
  }
  return X;
}
