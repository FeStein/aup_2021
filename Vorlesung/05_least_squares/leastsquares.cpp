#include <fstream>
#include <iostream>
#include <math.h>

void gauss(double *m, double *x, double *r, int n);

int main() {
  //--------------Einlesen der Funktionsdaten-------------
  std::ifstream ifile;

  // File Länge checken
  int n = 0;
  double x, y;
  ifile.open("xy_data.dat");
  while (ifile >> x >> y) {
    n += 1;
  }
  ifile.close();

  double *xarr, *yarr;

  xarr = new double[n];
  yarr = new double[n];

  // Daten Einlesen
  ifile.open("xy_data.dat");
  for (int i = 0; i < n; ++i) {
    ifile >> xarr[i] >> yarr[i];
  }
  ifile.close();

  //------------Least Squares----------------------------
  int npoly = 5;
  int mind = 0;

  double *marr, *aarr, *rarr;
  marr = new double[(npoly + 1) * (npoly + 1)];
  aarr = new double[(npoly + 1)];
  rarr = new double[(npoly + 1)];

  // Matrix:
  for (int i = 0; i <= npoly; ++i) {
    for (int j = 0; j <= npoly; ++j) {
      mind = i * (npoly + 1) + j;
      marr[mind] = 0.;
      for (int k = 0; k < n - 1; ++k) {
        marr[mind] += pow(xarr[k], j) * pow(xarr[k], i);
      }
    }
  }
  // RHS:
  for (int i = 0; i <= npoly; ++i) {
    rarr[i] = 0.;
    for (int k = 0; k < n-1; ++k) {
      rarr[i] += yarr[k] * pow(xarr[k], i);
    }
  }
  // Koeff:
  gauss(marr, aarr, rarr, npoly + 1);

  //------------Koeff Ausgabe----------------------------
  for (int i = 0; i <= npoly; ++i) {
    std::cout << aarr[i] << std::endl;
  }

  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i <= npoly; ++i) {
    ofile << aarr[i] << std::endl;
  }
  ofile.close();

  //------------Post Processing--------------------------
  delete[] xarr;
  delete[] yarr;
  delete[] marr;
  delete[] aarr;
  delete[] rarr;

  return 0;
}
