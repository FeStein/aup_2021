#include <fstream>
#include <iostream>
#include <math.h>

int main(int argc, char *argv[]) {
  // Parameter
  double alpha = 10., lambda = 15., A = 0.001, U = 0.22, L = 0.3, c = 500.,
         rho = 7600.;
  double Ta = 423., Tu = 150.;
  double dx, a, dt;

  int nl = 100; // Diskretisierung
  int nt = 800; // Zeitschritte

  a = lambda / (rho * c);

  dx = L / (nt -1);
	dt = 0.4 * dx * dx/a;

  double *T;

  T = new double[nt];
  
  // Anfangsbedingung und Randbedingung
  T[0] = Ta;
  for (int i = 1; i < nl; i++) {
    T[i] = Tu;
  }

  double Tbf;
  
  // Zeitschrittverfahren
  for (int ti = 0; ti < nt; ti++) {
    Tbf = T[0];
    for (int li = 1; li < nl - 1; li++) {
      T[li] = a * dt *(T[li + 1] - 2 * T[li] + Tbf) / (dx * dx) - (alpha * U * dt) /(rho * A * c) * (T[li] - Tu) + T[li];
      Tbf = T[li]; 
    } 
  } 

  //Output
  std::ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < nl; i++) {
    ofile << i*dx << " " << T[i] << std::endl; 
  }
  ofile.close();

  std::cout << "Differenzenvefahren explizit erfolgreich durchgeführt" << std::endl;

  return 0;
}
