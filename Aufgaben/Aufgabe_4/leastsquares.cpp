#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

std::vector<double> gauss_seidel(std::vector<std::vector<double>> ARRM, std::vector<double> R);

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

  // create ARRM + RHS
  std::vector<std::vector<double>> ARRM(n, std::vector<double>(n, 0.0));
  std::vector<double> RHS(n,0.0);

  // fill ARRM + RHS
  for (int i = 0; i < m; ++i) {
    ARRM[0][0] += sqrt(ARRX[i]) * sqrt(ARRX[i]);
    RHS[0] += sqrt(ARRX[i]) * ARRY[i];
  }
  for (int row = 1; row < n; ++row) {
    for (int col = 1; col < n; ++col) {
      for (int i = 0; i < m; ++i) {
        ARRM[row][col] += pow(ARRX[i],col) * pow(ARRX[i],row);
      }
    }
    for (int i = 0; i < m; ++i) {
      // use symmetry
      ARRM[row][0] += pow(ARRX[i],row) * sqrt(ARRX[i]);
      ARRM[0][row] += pow(ARRX[i],row) * sqrt(ARRX[i]);
      RHS[row] += pow(ARRX[i],row) * ARRY[i];
    }
  }
  
  // Solve
  std::vector<double> ARRA = gauss_seidel(ARRM,RHS);
  
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
  int num_iter = 10;
  int n = R.size();
  std::vector<double> X(n,1.0);
  std::vector<double> XBF(n,1.0);

  double sigma;
  for (int iter = 0; iter < num_iter; iter++) {
    
    for (int i = 0; i < n; i++) {
      sigma = 0;
      for (int j = 0; j < n; j++) {
        if (i != j){
          sigma += M[i][j]*XBF[j];
        }
      }
      X[i] = (1/M[i][i]) * (R[i] - sigma);
    }
    for (int i = 0; i < n; i++) {
      XBF[i] = X[i];
    }
  }

  for (int i = 0; i < n; i++) {
    std::cout << X[i] << std::endl;
  }
  return X;
}
