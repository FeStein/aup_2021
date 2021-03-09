#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>

int main() {
  double *M;
  double a, b, epsilon;
  int n = 100;
  int c = 0;

  M = new double[n];

  a = 1.;
  b = 1.5;
  epsilon = 0.00001;

  M[0] = (a + b) / 2; // Initial guess

  // Newton
  double f, fs, x;
  for (int i = 1; i < n; ++i) {
    x = M[i - 1];
    f = sin(x * x / 2 * M_PI);
    fs = cos(x * x / 2 * M_PI) * x * M_PI;
    if (fabs(f) < epsilon) {
      break;
    }
    c++;
    M[c] = x - f / fs;
  }

  // Output
  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i <= c; ++i) {
    ofile << M[i] << std::endl;
  }
  ofile.close();

  std::cout << "Root: " << M[c] << " found after " << c << " iterations" << std::endl;

  delete[] M;

  return 0;
}
