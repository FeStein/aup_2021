#include <fstream>
#include <math.h>
#include <iostream>

double integral(double *X, double *Y, int n);

int main()
{
  // read input
  std::ifstream ifile; 
  int n;
  n = 0;
  double x,y;
  ifile.open("signal.dat");
  while(ifile >> x >> y){
    n++; 
  }
  ifile.close();

  double *T, *S;
  T = new double[n];
  S = new double[n];
  ifile.open("signal.dat");
  for (int i = 0; i < n; ++i) {
    ifile >> T[i] >> S[i];
  }
  ifile.close();

  // define problem
  double omega = (2 * M_PI)/5.;
  double *AK,*BK;
  int m = 100;
  AK = new double[m];
  BK = new double[m];

  double *INT;
  INT = new double[n];
  for (int k = 0; k < m; k++) {
    for (int i = 0; i < n; ++i) {
      INT[i] = S[i] * cos(k * omega * T[i]);
    }
    AK[k] = (2./5.) * integral(T,INT,n);
    for (int i = 0; i < n; ++i) {
      INT[i] = S[i] * sin(k * omega * T[i]);
    }
    BK[k] = (2./5.) * integral(T,INT,n);

    //Filtern der werte
    //if (2 * M_PI * k > 3000) {
    //  A[k] = A[k] / 2;
    //  B[k] = B[k] / 2;
    //}
  }
  //Creat output
  double *OUT;
  OUT = new double [n];
  double sum1, sum2;  

  for (int i = 0; i < n; ++i) {
    sum1 = 0;
    sum2 = 0;
    for (int k = 1; k < m; ++k) {
      sum1 += AK[k] * cos(k * omega * T[i]);
      sum2 += BK[k] * sin(k * omega * T[i]);
    }  
    OUT[i] = (AK[0] / 2) + sum1 + sum2;
  }

  //Ausgabe
  std::ofstream ofile;
  ofile.open("output");
  for(int i = 0; i < n; ++i){
    ofile << T[i] << " " << S[i] << " " << OUT[i] << std::endl;
  }
  ofile.close();

  delete [] INT;
  delete [] OUT;
  delete [] AK;
  delete [] BK;
  delete [] S;
  delete [] T;
  
  return 0;
}


double integral(double *X, double *Y, int n){
  double a = 0;
  for (int i = 0; i < n-1; ++i) {
    a += (Y[i] + Y[i+1]) * 0.5 * (X[i+1] - X[i]);
  }
  return a;
}
