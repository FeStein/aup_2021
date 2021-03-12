#include <fstream>
#include <iostream>
#include <math.h>
#include <mutex>
#include <vector>

double integral(const std::vector<double> &X, const std::vector<double> &Y);
std::vector<double> grenzschicht(const std::vector<double> &Y, double U);
double H(double U);

int main() {
  int n = 101;
  double dx, U;
  dx = 10. / (n - 1);

  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    U = -5 + i * dx;
    ofile << U << "," << H(U) << std::endl;
  }
  ofile.close();

  return 0;
}

double H(double U) {
  int n;
  double delta, dy, deltas, sigma;
  n = 101;     // Discretization
  delta = 0.1; // fix, should be given
  std::vector<double> Y;
  dy = (0.0 + delta) / (n - 1.0);

  // create base vector
  for (int i = 0; i < n; ++i) {
    Y.push_back(dy * i);
  }

  std::vector<double> KLEINU = grenzschicht(Y, U);
  std::vector<double> INT(n, 0.0);

  for (int i = 0; i < n; ++i) {
    INT[i] = (1 - KLEINU[i] / U);
  }
  deltas = integral(Y, INT);
  std::cout << deltas << std::endl;

  for (int i = 0; i < n; ++i) {
    INT[i] = (1 - KLEINU[i] / U) * (KLEINU[i] / U);
  }
  sigma = integral(Y, INT);

  std::cout << deltas << " " << sigma << std::endl;

  return deltas / sigma;
}

double integral(const std::vector<double> &X, const std::vector<double> &Y) {
  int n = X.size();
  double sum = 0.0;
  for (int i = 0; i < n - 1; ++i) {
    sum += (Y[i] + Y[i + 1]) * 0.5 * (X[i + 1] - X[i]);
  }
  return sum;
}

std::vector<double> grenzschicht(const std::vector<double> &Y, double U) {
  int n = Y.size();
  std::vector<double> KLEINU(n, 1.0); // example sinze real fun is not given
  for (int i = 0; i < n; ++i) {
    KLEINU[i] = 3.0; 
  }
  return KLEINU;
}
