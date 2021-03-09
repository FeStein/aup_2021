#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <memory>

int main() {
  double a, b, epsilon;
  int n = 100;
  int c = 0;

  auto M = std::unique_ptr<double[]>(new double[n]);

  a = 1.;
  b = 1.5;
  epsilon = 0.00001;

  M[0] = (3*a + b) / 4; // Initial guess
  M[1] = (a + 3*b) / 4; // Initial guess

  // Newton
  double f, fs, x;
  for (int i = 2; i < n; ++i) {
    x = M[i - 1];
    f = sin(x * x / 2 * M_PI);
    fs = cos(x * x / 2 * M_PI) * x * M_PI;
    std::cout << fabs(f) << std::endl;
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

  return 0;
}
