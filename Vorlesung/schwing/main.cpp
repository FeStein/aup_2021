#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main() {
  double T = 8., D = 1., k = 5., m = 1., g = 9.81, V0 = 1.;
  int n = 1000;
  double k1x, k2x, k3x, k4x, kx;
  double k1y, k2y, k3y, k4y, ky;

  double *x, *y, *t;

  double dt = T / (n - 1);
  t = new double[n];
  x = new double[n];
  y = new double[n];

  // Anfangsbedingungen
  t[0] = 0.;
  x[0] = 0.;
  y[0] = V0;

  // Runge Kutta Verfahren
  for (int i = 1; i <= n; ++i) {
    t[i] = t[i - 1] + dt;

    // 1. Schritt
    k1y = g - D / m * y[i - 1] - k / m * x[i - 1];
    k1x = y[i - 1];

    // 2. Schritt
    k2y = g - D / m * (y[i - 1] + k1y * dt / 2.) -
          k / m * (x[i - 1] + k1x * dt / 2.);
    k2x = y[i - 1] + k1y * dt / 2.;

    // 3. Schritt
    k3y = g - D / m * (y[i - 1] + k2y * dt / 2.) -
          k / m * (x[i - 1] + k2x * dt / 2.);
    k3x = y[i - 1] + k2y * dt / 2.;

    // 4.Schritt
    k4y = g - D / m * (y[i - 1] + k3y * dt / 2.) -
          k / m * (x[i - 1] + k3x * dt / 2.);
    k4x = y[i - 1] + k3y * dt / 2.;

    kx = (k1x + 2. * k2x + 2. * k3x + k4x) / 6.;
    ky = (k1y + 2. * k2y + 2. * k3y + k4y) / 6.;

    x[i] = x[i - 1] + kx * dt;
    y[i] = y[i - 1] + ky * dt;
  }

  FILE *fin;
  fin = fopen("schwing.dat", "w");
  for (int i = 0; i <= n; ++i) {
    fprintf(fin, "%15.6lf, %15.6lf, %15.6lf\n", t[i], x[i], y[i]);
  }

  delete[] t;
  delete[] x;
  delete[] y;

  std::cout << "working fine" << std::endl;

  return 0;
}
