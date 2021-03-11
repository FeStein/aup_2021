#include <iostream>
#include <vector>

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
