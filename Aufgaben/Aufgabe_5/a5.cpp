#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

std::vector<double> gauss(std::vector<std::vector<double>> M, std::vector<double> R);

double dF(const std::vector<double> &AX, const std::vector<double> &AY, double a, double b, double c);

std::vector<double> ac_eq(const std::vector<double> &AX, const std::vector<double> &AY, double b);

int main() {
  double x, y, dx, disk;

  disk = 201; // number of x values for output
  int m;

  // read in the data
  std::vector<double> AX;
  std::vector<double> AY;

  std::ifstream ifile;
  ifile.open("IN.dat");
  while (ifile >> x >> y) {
    AX.push_back(x);
    AY.push_back(y);
  }
  ifile.close();
  m = AX.size();

  double b1, b2, F1, F2, bk;

  // intial guess of 2 b values
  b1 = -1.25;
  b2 = -1.0;
  std::vector<double> KOEFF;

  KOEFF = ac_eq(AX, AY, b1);
  F1 = dF(AX, AY, KOEFF[0], b1, KOEFF[1]);

  KOEFF = ac_eq(AX, AY, b2);
  F2 = dF(AX, AY, KOEFF[0], b2, KOEFF[1]);
  
  // This is some debug output
  dx = 10 / (disk - 1);
  double y2;
  std::ofstream ofile;
  ofile.open("dF");
  for (int i = 0; i < disk; ++i) {
    x = -5 + dx * i;
    KOEFF = ac_eq(AX, AY, x);
    y = dF(AX, AY, KOEFF[0], x, KOEFF[1]);
    y2 = 0;
    for (int i = 0; i < m; ++i) {
      y2 += pow(AY[i] - KOEFF[0] * pow(AX[i],x) - KOEFF[1],2) ;
    }
    ofile << x << " " << y << " " << y2 << std::endl;
  }
  ofile.close();


  int max_iter = 200;

  while (fabs(F2) > 0.00001  && max_iter > 0) {
    max_iter--;
    bk = b2 - (F2 /(F2 - F1)) * (b2 - b1);
    b1 = b2;
    b2 = bk;
    F1 = F2;
    KOEFF = ac_eq(AX, AY, b2);
    F2 = dF(AX, AY, KOEFF[0], b2, KOEFF[1]);
    std::cout << bk << std::endl;
  }

  std::cout << "final b: " << b2 << std::endl;
  // output
  dx = (AX.back() - AX.front()) / (disk - 1);

  KOEFF = ac_eq(AX, AY, b2);
  //ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < disk; ++i) {
    x = AX.front() + dx * i;
    y = KOEFF[0] * pow(x, b2) + KOEFF[1];
    ofile << x << " " << y << std::endl;
  }
  ofile.close();

  return 0;
}

double dF(const std::vector<double> &AX, const std::vector<double> &AY, double a, double b, double c) {
  double out = 0.0;
  for (int i = 0; i < AX.size(); ++i) {
    out += (AY[i] - (a * pow(AX[i], b) + c)) * (a * pow(AX[i], b) * log(AX[i]));
  }
  return out;
}

// ac equation task c) returns {a c} (koefficients)
std::vector<double> ac_eq(const std::vector<double> &AX, const std::vector<double> &AY, double b) {
  double phi;
  int m;
  m = AX.size();

  // create lse
  std::vector<std::vector<double>> M(2, std::vector<double>(2, 0.0));
  std::vector<double> B(2, 0.0);
  for (int i = 0; i < m; ++i) {
    phi = pow(AX[i], b);
    M[0][0] += phi * phi;
    M[0][1] += phi;
    M[1][0] += phi;
    M[1][1] += 1;
    B[0] += AY[i] * phi;
    B[1] += AY[i];
  }

  return gauss(M, B);
}

std::vector<double> gauss(std::vector<std::vector<double>> M, std::vector<double> R) {

  int n = R.size();
  std::vector<double> X(n, 0.0);
  int i, j, k;

  //forward substitution
  for (i = 0; i < n - 1; i++) {
    for (k = i + 1; k < n; k++) {
      for (j = i; j < n; j++) {
        X[j] = -M[i][j] * M[k][i] / M[i][i];
      }

      R[k] = R[k] - R[i] * M[k][i] / M[i][i];

      for (j = i; j <= n - 1; j++) {
        M[k][j] = M[k][j] + X[j];
      }
    }
  }

  // backwards substitution
  X[n - 1] = R[n - 1] / M[(n - 1)][n - 1];

  for (i = n - 2; i >= 0; i--) {
    X[i] = R[i];
    for (j = i + 1; j < n; j++) {
      X[i] = X[i] - M[i][j] * X[j];
    }

    X[i] = X[i] / M[i][i];
  }
  return X;
}
