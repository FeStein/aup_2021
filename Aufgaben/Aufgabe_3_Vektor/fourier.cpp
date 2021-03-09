#include <fstream>
#include <math.h>
#include <iostream>
#include <vector>

double integral(std::vector<double> X, std::vector<double> Y);

int main()
{
  // read input via vector
  std::vector<double> T;
  std::vector<double> S;

  std::ifstream ifile; 
  ifile.open("signal.dat");
  double x,y;
  while(ifile >> x >> y){
    T.push_back(x);
    S.push_back(y);
  }
  ifile.close();

  double omega = (2 * M_PI)/5.;
  int m = 100;
  int n = T.size();

  std::vector<double> AK;
  std::vector<double> BK;

  std::vector<double> INT(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cout << INT[i] << std::endl; 
  }

  for (int k = 0; k < m; k++) {
    for (int i = 0; i < n; ++i) {
      INT[i] = S[i] * cos(k * omega * T[i]);
    }
    AK.push_back((2./5.) * integral(T,INT));
    for (int i = 0; i < n; ++i) {
      INT[i] = S[i] * sin(k * omega * T[i]);
    }
    BK.push_back((2./5.) * integral(T,INT));
  }

  //Creat output
  double sum1, sum2, out;  
  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    sum1 = 0;
    sum2 = 0;
    for (int k = 1; k < m; ++k) {
      sum1 += AK[k] * cos(k * omega * T[i]);
      sum2 += BK[k] * sin(k * omega * T[i]);
    }  
    out = (AK[0] / 2) + sum1 + sum2;
    ofile << T[i] << " " << S[i] << " " << out << std::endl;
  }

  return 0;
}

double integral(std::vector<double> X, std::vector<double> Y){
  double a = 0;
  for (int i = 0; i < X.size()-1; ++i) {
    a += (Y[i] + Y[i+1]) * 0.5 * (X[i+1] - X[i]);
  }
  return a;
}
