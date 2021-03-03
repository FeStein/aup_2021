#include "integration.h"
#include <fstream>
#include <iostream>
#include <math.h>

int main() {
  //--------------Input-------------------------------
  double *t_val, *y_val;

  // Read input File
  std::ifstream input_file;
  input_file.open("input.dat");

  // Check number of lines in input File
  int n = 0;
  double x, y;
  while (input_file >> x >> y) {
    n = n + 1;
  }

  t_val = new double[n];
  y_val = new double[n];

  input_file.close();
  input_file.open("input.dat");

  // Read Values
  for (int i = 0; i < n; ++i) {
    input_file >> t_val[i] >> y_val[i];
  }
  input_file.close();

  //--------------Fourier-----------------------------
  int nk = 100;
  double T = 2.;
  double omega = (2 * M_PI) / T;

  double *ak, *bk, *iak, *ibk;

  ak = new double[nk];
  bk = new double[nk];
  iak = new double[n]; // Aufpunkte zur Integration
  ibk = new double[n]; // Aufpunkte zur Integration

  // Berechne Fourier Koeffizienten ak, bk
  for (int k = 0; k <= nk; ++k) {

    for (int i = 0; i < n; ++i) {
      iak[i] = y_val[i] * cos(k * omega * t_val[i]);
    }
    ak[k] = (2. / T) * integration_simpson(t_val, iak, n);

    // Berechnung bk
    if (k > 0) {
      for (int i = 0; i < n; ++i) {
        ibk[i] = y_val[i] * sin(k * omega * t_val[i]);
      }
      bk[k] = (2. / T) * integration_simpson(t_val, ibk, n);
    }
  }
  // Approximate the function
  double sa, sb;
  double *fapprox;
  fapprox = new double[n];
  for (int i = 0; i < n; ++i) {
    sa = 0;
    sb = 0;
    // ak Teil
    for (int k = 1; k <= nk; ++k) {
      sa += ak[k] * cos(k * omega * t_val[i]);
    }
    // bk Teil
    for (int k = 1; k <= nk; ++k) {
      sb += bk[k] * sin(k * omega * t_val[i]);
    }

    fapprox[i] = (ak[0] / 2) + sa + sb;
  }

  //--------------Output-------------------------------
  std::ofstream output_file;
  output_file.open("output");

  for (int i = 0; i < n; ++i) {
    output_file << t_val[i] << " " << y_val[i] << " " << fapprox[i]
                << std::endl;
  }
  output_file.close();

  //--------------Dereferenzierung--------------------
  std::cout << "Zum Plotten des Outputs: python3 plot.py" << std::endl;
  delete[] t_val;
  delete[] y_val;
  delete[] ak;
  delete[] bk;
  delete[] iak;
  delete[] ibk;

  return 0;
}
