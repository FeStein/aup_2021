#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

std::vector<double> gauss_seidel(std::vector<std::vector<double>> M,
                                 std::vector<double> R);

vector<double> ac_eq(vector<double> AX, vector<double> AY, double b);

double dF(vector<double> AX, vector<double> AY, double a, double b, double c);

int main() {
  double x, y, b, dx, disk;

  disk = 201; // number of x values for output
  int m;

  // read in the data
  vector<double> AX;
  vector<double> AY;

  ifstream ifile;
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
  vector<double> KOEFF;

  KOEFF = ac_eq(AX, AY, b1);
  F1 = dF(AX, AY, KOEFF[0], b1, KOEFF[1]);

  KOEFF = ac_eq(AX, AY, b2);
  F2 = dF(AX, AY, KOEFF[0], b2, KOEFF[1]);
  
  // This is some debug output
  dx = 10 / (disk - 1);
  double y2;
  ofstream ofile;
  ofile.open("dF");
  for (int i = 0; i < disk; ++i) {
    x = -5 + dx * i;
    KOEFF = ac_eq(AX, AY, x);
    y = dF(AX, AY, KOEFF[0], x, KOEFF[1]);
    y2 = 0;
    for (int i = 0; i < m; ++i) {
      y2 += pow(AY[i] - KOEFF[0] * pow(AX[i],x) - KOEFF[1],2) ;
    }
    ofile << x << " " << y << " " << y2 << endl;
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
    cout << bk << endl;
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
    ofile << x << " " << y << endl;
  }
  ofile.close();

  return 0;
}

double dF(vector<double> AX, vector<double> AY, double a, double b, double c) {
  double out = 0.0;
  for (int i = 0; i < AX.size(); ++i) {
    out += (AY[i] - (a * pow(AX[i], b) + c)) * (a * pow(AX[i], b) * log(AX[i]));
  }
  return out;
}

// ac equation task c) returns {a c} (koefficients)
vector<double> ac_eq(vector<double> AX, vector<double> AY, double b) {
  double phi;
  int m;
  m = AX.size();

  // create lse
  vector<vector<double>> M(2, vector<double>(2, 0.0));
  vector<double> B(2, 0.0);
  for (int i = 0; i < m; ++i) {
    phi = pow(AX[i], b);
    M[0][0] += phi * phi;
    M[0][1] += phi;
    M[1][0] += phi;
    M[1][1] += 1;
    B[0] += AY[i] * phi;
    B[1] += AY[i];
  }

  return gauss_seidel(M, B);
}

// gauss seidel algorithm
std::vector<double> gauss_seidel(std::vector<std::vector<double>> M,
                                 std::vector<double> R) {
  int num_iter = 10000;
  int n = R.size();
  std::vector<double> X(n, 1.0);
  std::vector<double> XBF(n, 1.0);

  double sigma;
  for (int iter = 0; iter < num_iter; iter++) {

    for (int i = 0; i < n; i++) {
      sigma = 0;
      for (int j = 0; j < n; j++) {
        if (i != j) {
          sigma += M[i][j] * XBF[j];
        }
      }
      X[i] = (1 / M[i][i]) * (R[i] - sigma);
    }
    for (int i = 0; i < n; i++) {
      XBF[i] = X[i];
    }
  }
  return X;
}
