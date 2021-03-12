#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

double cw(double h);

int main() {
  int max_iter = 100000;
  double phi = 0.01;
  double g = 9.81;

  // Starting cond
  std::vector<double> T = {0.0};
  std::vector<double> X = {5000.0};
  std::vector<double> Y = {0.0};

  double k1x, k2x, k3x, k4x, kx;
  double k1y, k2y, k3y, k4y, ky;

  double dt = 0.1;

  std::ofstream ofile;
  ofile.open("output");
  ofile << T.back() << "," << X.back() << "," << Y.back() << std::endl;

  double xi, yi;
  int i = 0;
  while (X.back() > 0 ) {
    i++;
    if (i > max_iter) break;
    T.push_back(i * dt);

    // step 1
    xi = X.back();
    yi = Y.back();
    k1y = -g + cw(xi) * pow(yi, 2) * phi;
    k1x = yi;

    // step 2
    xi = X.back() + k1x * (dt / 2.0);
    yi = Y.back() + k1y * (dt / 2.0);
    k2y = -g + cw(xi) * pow(yi, 2) * phi;
    k2x = yi;

    // step 3
    xi = X.back() + k2x * (dt / 2.0);
    yi = Y.back() + k2y * (dt / 2.0);
    k3y = -g + cw(xi) * pow(yi, 2) * phi;
    k3x = yi;

    // step 4
    xi = X.back() + k3x * (dt);
    yi = Y.back() + k3y * (dt);
    k4y = -g + cw(xi) * pow(yi, 2) * phi;
    k4x = yi;

    kx = (k1x + 2. * k2x + 2. * k3x + k4x) / 6.;
    ky = (k1y + 2. * k2y + 2. * k3y + k4y) / 6.;

    X.push_back(X.back() + kx * dt);
    Y.push_back(Y.back() + ky * dt);

    // Ausgabe
    ofile << T.back() << "," << X.back() << "," << Y.back() << std::endl;
  }

  ofile.close();

  return 0;
}

double cw(double h) {
  if (h > 2000) {
    return 0.2;
  } else {
    return 5.0;
  }
}
