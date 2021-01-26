#include "integ_algo.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

// Programming rectangle function as fourier transformation

int main() {
  // alias for pi constant.
  double pi = M_PI;

  // number of fourier coefficients.
  int n = 30;
  // number of interpolation points -> used for numerical integration.
  int m = 0;

  // constants and variables.
  double T = 2., freq = 1 / T, omega, k, integ, step;

  // arrays to save function points.
  double *a_k, *b_k, *t_val, *y_val, *f, *fapprox;

  omega = 2. * pi * freq;

  // get m -> number of rows in input data.
  ifstream indexfile("input.dat");
  string line;
  while (getline(indexfile, line)) {
    m++;
  }

  t_val = new double[m];
  y_val = new double[m]; // later values server as integration points
  f = new double[m];

  // read in x_values and function values.
  ifstream ifile("input.dat");
  int index = 0;
  while (!ifile.eof()) {
    ifile >> t_val[index];
    ifile >> f[index];
    index++;
  }

  a_k = new double[n];
  b_k = new double[n];

  // calcualte fourier coefficients
  for (int i = 0; i < n; i++) {

    // calculate a_k
    for (int j = 0; j < m; j++) {
      y_val[j] = f[j] * cos(i * omega * t_val[j]);
    }
    a_k[i] = (2. / T) * trapez(t_val, y_val, m);
    // calculate b_k
    for (int j = 0; j < m; j++) {
      y_val[j] = f[j] * sin(i * omega * t_val[j]);
    }
    b_k[i] = (2. / T) * trapez(t_val, y_val, m);
  }

  double suma, sumb;
  // calculate approximation of f
  fapprox = new double[m];
  for (int i = 0; i < m; i++) {
    suma = 0;
    sumb = 0;

    // part a_k
    for (int j = 1; j < n; j++) {
      suma += a_k[j] * cos(j * 2 * pi * t_val[i] * freq);
    }
    // part b_k
    for (int j = 1; j < n; j++) {
      sumb += b_k[j] * sin(j * 2 * pi * t_val[i] * freq);
    }

    fapprox[i] = (a_k[0] / 2) + suma + sumb;
  }

  // print approximation to file
  ofstream ofile;
  ofile.open("approx.dat");

  for (int i = 0; i < m; i++) {
    ofile << t_val[i] << " " << f[i] << " " << fapprox[i] << endl;
  }

  ofile.close();

  delete[] a_k;
  delete[] b_k;
  delete[] t_val;
  delete[] y_val;
  delete[] f;
  delete[] fapprox;

  return 0;
}
