#include <iostream>
#include <math.h>
#include <fstream>

void thomas(double *MAT, double *RHS, double *SOL, int n);

int main() {
  double alpha = 10., lambda = 15., A = 0.001, U = 0.22, L = 0.3, c = 500.,
         rho = 7600.;
  double Ta = 423., Tu = 150.;
  double dx, a, dt;

	int n = 100;
	int M = 800;

  a = lambda / (rho * c);

  // Diskretisierung
  dx = L / (n - 1);
  dt = 0.4 * dx * dx / a;

  // Create Matrix
  double *MAT, *RHS, *SOL;

  MAT = new double [n * n];
  RHS = new double [n];
  SOL = new double [n];
  
  //Set initial Temperature to Tu
  for (int i = 1; i < n; ++i) {
    SOL[i] = Tu;
  }
  SOL[0] = Ta;

  for (int t = 0; t < M-1; ++t) {
    // Matrix befüllen
    for (int j = 0; j < n; j++) {
      if ((j != 0) && (j != n-1)) {
        MAT[j * n + j - 1] = - a / (dx * dx) * dt; // Bi
        MAT[j * n + j] = 1. + 2. * a * dt/( dx * dx ) + alpha * U * dt/( rho * A * c); // Di
        MAT[j * n + j + 1] = MAT[j * n + j - 1]; // Ai
      }
      RHS[j] = Tu * (alpha * U * dt) / (rho * A * c)  + SOL[j];
    }

    // Randbedingungen
    MAT[0] = 1;
    MAT[1] = 0;

    MAT[n * n - 1] = 1;
    MAT[n * n - 2] = 0;

    RHS[0] = Ta;
    RHS[n - 1] = Tu;

    // Solve
    thomas(MAT, RHS, SOL, n);
  } 
  
  //Output
  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    ofile << i*dx << " " << SOL[i] << std::endl; 
  }
  ofile.close();

  std::cout << "Temperaturberechnung implizit abgeschlossen" << std::endl;

  delete [] MAT;
  delete [] RHS;
  delete [] SOL;

  return 0;
}

void thomas(double *MAT, double *RHS, double *SOL, int n) {

  double z, nn;

  // Rekursive Komponentenmodifikation (Vorwärtsdurchlauf)
  MAT[1] = MAT[1] / MAT[0];
  for (int i = 1; i < n - 1; ++i) {
    MAT[n * i + i + 1] =
        MAT[n * i + i + 1] /
        (MAT[n * i + i] - MAT[n * (i - 1) + i - 1 + 1] * MAT[n * i + i - 1]);
  }
  RHS[0] = RHS[0] / MAT[0];
  for (int i = 1; i < n; ++i) {
    z = RHS[i] - RHS[i - 1] * MAT[n * i + i - 1];
    nn = MAT[n * i + i] - MAT[n * (i - 1) + i - 1 + 1] * MAT[n * i + i - 1];
    RHS[i] = z / nn;
  }

  // Rückwärts Substituion
  SOL[n - 1] = RHS[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    SOL[i] = RHS[i] - MAT[n * i + i + 1] * SOL[i + 1];
  }
}
