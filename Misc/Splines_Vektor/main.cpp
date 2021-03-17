#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

std::vector<double> gauss(std::vector<std::vector<double>> M,
                          std::vector<double> R);

int main() {

  // Read file
  double x, y;
  std::vector<double> X, Y;
  std::ifstream ifile;
  ifile.open("input");
  while (ifile >> x >> y) {
    X.push_back(x);
    Y.push_back(y);
  }
  ifile.close();
  int n = X.size();

  // create LSE for splines
  std::vector<std::vector<double>> M(n, std::vector<double>(n, 0.0));
  std::vector<double> RHS(n, 0.0);
  M.front().front() = 1;
  M.back().back() = 1;

  double hi, hi_1;

  for (int i = 1; i < n - 1; ++i) {
    hi = X[i + 1] - X[i];
    hi_1 = X[i] - X[i - 1];
    M[i][i - 1] = hi_1;
    M[i][i] = 2 * (hi_1 + hi);
    M[i][i + 1] = hi;
    RHS[i] = (6 / hi) * (Y[i + 1] - Y[i]) - (6 / hi_1) * (Y[i] - Y[i - 1]);
  }

  std::vector<double> YS = gauss(M, RHS);

  // Calculate koeff
  // for (int i = 0; i < n - 1; ++i) {
  //  hi = X[i + 1] - X[i];
  //  KOEFF[i][0] = (YS[i + 1] - YS[i]) / (6.0 * hi);
  //  KOEFF[i][1] = YS[i] / 2.0;
  //  KOEFF[i][2] = (Y[i + 1] - Y[i]) / hi - hi * (YS[i + 1] + 2 * YS[i]) / 6;
  //  KOEFF[i][3] = Y[i];
  //}

  std::ofstream ofile;
  ofile.open("output");
  double dx, xi;
  double a, b, c, d;
  int m = 1001, si;
  dx = (X.back() - X.front()) / (m - 1);
  for (int i = 0; i < m-1; ++i) {
    x = X.front() + i * dx;
    si = 0;
    // this implementation is very very bad
    while (x >= X[si]) {
      si++;
    }
    si--;
    xi = X[si];
    hi = X[si + 1] - X[si];

    // get koeff
    a = (YS[si + 1] - YS[si]) / (6.0 * hi);
    b = YS[si] / 2.0;
    c = (Y[si + 1] - Y[si]) / hi - hi * (YS[si + 1] + 2 * YS[si]) / 6;
    d = Y[si];
    y = a * pow(x - xi, 3) + b * pow(x - xi, 2) + c * pow(x - xi, 1) + d;
    ofile << x << "," << y << std::endl;
  }
  ofile.close();

  return 0;
}

std::vector<double> gauss(std::vector<std::vector<double>> M,
                          std::vector<double> R) {

  int n = R.size();
  std::vector<double> X(n, 0.0);
  int i, j, k;

  // forward substitution
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
