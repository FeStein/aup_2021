#include <iostream>
#include <vector>

std::vector<double> gauss_seidel(std::vector<std::vector<double>> M, std::vector<double> R, int num_iter = 100) {

  int n = R.size();
  std::vector<double> XN(num_iter,0.0);
  std::vector<double> X(n,0.0);

  double sum;
  for (int b = 0; b < num_iter; ++b) {
    for (int k = 0; k < n; ++k) {
      sum = 0;
      for (int j = 0; j < n; ++j) {
        if (j != k) {
          sum += M[k][j] * X[j];
        }
      }
      XN[k] = (1 / M[k][k]) * (R[k] - sum);
    }
    // Alter wert mit neuem Schätzwert überschreiben
    for (int i = 0; i < n; ++i) {
      X[i] = XN[i];
    }
  }

  return X;
}
