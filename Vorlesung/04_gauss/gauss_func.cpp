#include <iostream>

void gauss_seidel(double *m, double *x, double *r, int n) {
  double *xn;

  int num_iter = 100;

  xn = new double[n];

  // Initialer Vektor erzeugen (Schätzung)
  for (int k = 0; k < n; ++k) {
    x[k] = 0;
  }

  double sum;
  for (int b = 0; b < num_iter; ++b) {
    for (int k = 0; k < n; ++k) {
      sum = 0;
      for (int j = 0; j < n; ++j) {
        if (j != k) {
          sum += m[k * n + j] * x[j];
        }
      }
      xn[k] = (1 / m[k * n + k]) * (r[k] - sum);
    }
    // Alter wert mit neuem Schätzwert überschreiben
    for (int i = 0; i < n; ++i) {
      x[i] = xn[i];
    }
  }

  delete [] xn;

  return;
}
