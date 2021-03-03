#include <fstream>
#include <iostream>
#include <math.h>
void thomas(double *mat, double *RHS, double *SOL, int n);

int main() {
  //--------------Einlesen der Funktionsdaten-------------
  std::ifstream ifile;

  // File Länge checken
  int n;
  double x, y;
  ifile.open("xy_data.dat");
  n = 0;
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

  //--------------Kubische Splines-------------------------
  // Aufstellen Matrix
  double *mat, *h, *RHS;
  h = new double[n - 1];
  for (int i = 0; i < n - 1; ++i) {
    h[i] = xarr[i + 1] - xarr[i];
  }

  mat = new double[n * n];
  // Leere Matrix
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; j++) {
      mat[i * n + j] = 0.;
    }
  }

  // Randbedingungen
  mat[0] = 1.;
  mat[1] = 0;
  mat[n * n - 1] = 1.;
  mat[n * n - 2] = 0.;

  // Hautpdiagonale + 1. Nebendiagonalen befüllen
  for (int i = 1; i < n - 1; ++i) {
    mat[i * n + i - 1] = h[i - 1] / 6;      // bi
    mat[i * n + i] = (h[i - 1] + h[i]) / 3; // di
    mat[i * n + i + 1] = h[i] / 6;          // ai
  }

  // Rechte Seite
  RHS = new double[n];

  RHS[0] = 0;
  RHS[n - 1] = 0;
  for (int i = 1; i < n - 1; ++i) {
    RHS[i] =
        ((yarr[i + 1] - yarr[i]) / h[i]) - ((yarr[i] - yarr[i - 1]) / h[i - 1]);
  }

  double *SOL;
  SOL = new double[n];

  // Lösen
  thomas(mat, RHS, SOL, n);

  //Splines berechnen
  double *AI, *BI, *CI, *DI;

  AI = new double[n-1];
  BI = new double[n-1];
  CI = new double[n-1];
  DI = new double[n-1];

  for (int i = 0; i < n-1; ++i) {
    AI[i] = 1 / (6 * h[i]) * (SOL[i+1] - SOL[i]);
    BI[i] = SOL[i] / 2;
    CI[i] = (1/h[i])* (yarr[i+1] - yarr[i]) - (h[i] / 6) * (SOL[i+1] - 2* SOL[i]);
    DI[i] = yarr[i];
    std::cout << AI[i] << " " << BI[i] << " " << CI[i] << " " << DI[i] << " " << std::endl;
  }
  
  //--------------Ausgabe der Koeffizienten----------------
  std::ofstream ofile;
  ofile.open("output");

  for (int i = 0; i < n-1; ++i) {
    ofile << AI[i] << " "  << BI[i] << " "  << CI[i] << " "  << DI[i] << std::endl;
  }
  ofile.close();

  //for (int i = 0; i < n; ++i) {
  //  for (int j = 0; j < n; j++) {
  //    std::cout << mat[i * n + j] << " | ";
  //  }
  //  std::cout << std::endl;
  //}

  std::cout << "Created the splines" << std::endl;

  //--------------Post Processing--------------------------
  delete[] xarr;
  delete[] yarr;
  delete[] h;
  delete[] mat;
  delete[] SOL;
  delete[] RHS;
  delete[] AI;
  delete[] BI;
  delete[] CI;
  delete[] DI;

  return 0;
}

// Thomas Algorithmus -> Einfache Vorwärtssubstituion
void thomas(double *mat, double *RHS, double *SOL, int n) {

  double z, nn;

  // Rekursive Komponentenmodifikation (Vorwärtsdurchlauf)
  mat[1] = mat[1] / mat[0];
  for (int i = 1; i < n - 1; ++i) {
    mat[n * i + i + 1] =
        mat[n * i + i + 1] /
        (mat[n * i + i] - mat[n * (i -1) + i - 1 + 1] * mat[n * i + i - 1]);
  }
  RHS[0] = RHS[0] / mat[0];
  for (int i = 1; i < n; ++i) {
    z = RHS[i] - RHS[i - 1] * mat[n * i + i - 1];
    nn = mat[n * i + i] - mat[n * (i -1) + i - 1 + 1] * mat[n * i + i - 1];
    RHS[i] = z / nn;
  }

  // Rückwärts Substituion
  SOL[n - 1] = RHS[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    SOL[i] = RHS[i] - mat[n * i + i + 1] * SOL[i + 1];
  }
}
