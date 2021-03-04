#include <fstream>
#include <iostream>
#include <math.h>
void thomas(double *mat, double *RHS, double *SOL, int n);

int main() {
  // Anfangsbedingungen
  double q0 = 200, E = 2.1e11, J = 5.4e-7, l = 1.;
  double dx;
  int n;
  double *MAT, *RHS, *W, *X;

  n = 11;

  MAT = new double[n * n];
  RHS = new double[n];
  W = new double[n];
  X = new double[n];

  dx = l / (n - 1);

  // Randbedingungen
  MAT[0] = 1;
  MAT[1] = 0;

  MAT[n * n - 1] = 1;
  MAT[n * n - 2] = 0;

  RHS[0] = 0;
  RHS[n - 1] = 0;

  // Matrix befüllen
  for (int i = 0; i < n; ++i) {
    X[i] = i * dx;
    for (int j = 1; j < n - 1; j++) {
      MAT[j * n + j - 1] = 1.;
      MAT[j * n + j] = -2.;
      MAT[j * n + j + 1] = 1.;
    }
  }

  double zb, nb, fac;
  // Right Hand Side
  for (int i = 1; i < n - 1; ++i) {
    // x[i] * q0 * l * dx *dx/( 6. * E * J);
    zb = q0 * l * X[i] / l * l * dx * dx;
    nb = 6 * E * J;
    fac = pow(X[i] / l, 2) - 1;
    RHS[i] = (zb / nb) * fac;
  }

  thomas(MAT, RHS, W, n);

  //---------------------Output----------------------------------
  double w_analy;
  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    w_analy = q0 * pow(l, 4) / (360. * E * J) *
              (3. * pow(X[i] / l, 5) - 10. * pow(X[i] / l, 3) + 7. * X[i] / l);
    ofile << X[i] << " " << W[i] << " " << w_analy << " " << std::endl;
  }
  ofile.close();

  std::cout << "Berechung Balkenbiegung erfolgreich abgeschlossen" << std::endl;
  std::cout << "Achtung Balkenbiegung wird positiv dargestellt, da x-Achse "
               "nach unten verläuft"
            << std::endl;
  //---------------------Post Processing-------------------------

  delete[] MAT;
  delete[] RHS;
  delete[] W;
  delete[] X;

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
        (mat[n * i + i] - mat[n * (i - 1) + i - 1 + 1] * mat[n * i + i - 1]);
  }
  RHS[0] = RHS[0] / mat[0];
  for (int i = 1; i < n; ++i) {
    z = RHS[i] - RHS[i - 1] * mat[n * i + i - 1];
    nn = mat[n * i + i] - mat[n * (i - 1) + i - 1 + 1] * mat[n * i + i - 1];
    RHS[i] = z / nn;
  }

  // Rückwärts Substituion
  SOL[n - 1] = RHS[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    SOL[i] = RHS[i] - mat[n * i + i + 1] * SOL[i + 1];
  }
}
