#include <fstream>
#include <iostream>
#include <math.h>

int main() {
  double T = 8., D = 1., k = 5., m = 1., g = 9.81, V0 = 1.;
  int n = 1000;
  double *x, *y, *t;
  double k1x, k2x, k3x, k4x, kx;
  double k1y, k2y, k3y, k4y, ky;

  double dt = T / (n - 1);
  t = new double[n];
  x = new double[n];
  y = new double[n];

  // Starting cond
  t[0] = 0;
  x[0] = 0;
  y[0] = V0; // x'

  std::ofstream ofile;
  ofile.open("output");
  ofile << t[0] << " " << x[0] << " " << y[0] << std::endl;

  for (int i = 1; i < n; ++i) {

    t[i] = i * dt;

    // step 1
    k1y = g - D / m * y[i - 1] - k / m * x[i - 1];
    k1x = y[i - 1];

    // step 2
    k2y = g - D / m * (y[i - 1] + k1y * dt / 2.) -
          k / m * (x[i - 1] + k1x * dt / 2.);
    k2x = y[i - 1] + k1y * dt / 2.;

    // step 3
    k3y = g - D / m * (y[i - 1] + k2y * dt / 2.) -
          k / m * (x[i - 1] + k2x * dt / 2.);
    k3x = y[i - 1] + k2y * dt / 2.;

    // step 4
    k4y = g - D / m * (y[i - 1] + k3y * dt) - k / m * (x[i - 1] + k3x * dt);
    k4x = y[i - 1] + k3y * dt;

    kx = (k1x + 2. * k2x + 2. * k3x + k4x) / 6.;
    ky = (k1y + 2. * k2y + 2. * k3y + k4y) / 6.;

    x[i] = x[i - 1] + kx * dt;
    y[i] = y[i - 1] + ky * dt;

    // Ausgabe
    ofile << t[i] << " " << x[i] << " " << y[i] << std::endl;
  }

  ofile.close();

  delete[] t;
  delete[] x;
  delete[] y;

  return 0;
}
