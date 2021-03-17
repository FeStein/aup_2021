#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

std::vector<double> gauss(std::vector<std::vector<double>> M,
                          std::vector<double> R);


int main() {
  int n = 101;
  double dy;
  dy = 1.0 / (n - 1);

  vector<vector<double>> M(n, vector<double>(n, 0.0));
  vector<double> RHS(n, 0.0);

  // RB
  M.front().front() = 1.0;
  M.back().back() = 1.0;

  for (int i = 1; i < n - 1; ++i) {
    M[i][i - 1] = 1.0;
    M[i][i] = -2.0;
    M[i][i + 1] = 1.0;
    RHS[i] = pow(dy, 2);
  }
  vector<double> U = gauss(M, RHS);

  ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    ofile << i*dy << " " << U[i] << endl;
  }
  ofile.close();

  return 0;
}

std::vector<double> gauss(std::vector<std::vector<double>> M,
                          std::vector<double> R) {

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
