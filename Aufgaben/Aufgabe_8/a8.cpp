#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

int main() {
  double rho, lambda, cq, v, l, area, peri, alpha;
  double dx, dt, ca, cb;
  rho = 1000.0;
  lambda = 0.6;
  l = 20.0;
  cq = 4200.0;
  v = 0.1;
  area = 3.14 * pow(10, -4);
  peri = 0.0628;
  alpha = 2.5;

  ca = lambda / (rho * cq);
  cb = (alpha * peri) / (rho * area * cq);

  int diskret_x = 101;
  int diskret_t = 1000;

  dx = l / (diskret_x - 1);
  dt = 0.01;
  
  std::vector<double> T(diskret_x, 288.0);

  // boundary conditions
  T.front() = 318.0;
  std::vector<double> TB = T;

  for (int j = 0; j < diskret_t; j++) {
    for (int i = 1; i < diskret_x - 1; ++i) {
      T[i] = ca * dt * ((TB[i-1] + 2. * TB[i] + TB[i + 1]) / (2. * dx)) - cb * (TB[i] - 288.0) * dt - v * (TB[i] - TB[i-1]) * dt / dx + TB[i];
      TB = T;
    }
  }

  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < diskret_x; ++i) {
    ofile << i * dx << "," << T[i] << std::endl;
  }
  ofile.close();

  return 0;
}
