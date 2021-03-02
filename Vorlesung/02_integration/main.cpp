#include <iostream>
#include "integration.h"

double integration_trapez(double *x, double *y, int n);
double integration_simpson(double *x, double *y, int n);

int main() {
  // Anzahl an Aufpunkten.
  int n = 101;

  // Integrationsintervall [a;b].
  double a = 0.;
  double b = 3.;

  double dx;
  double itrapez;
  double isimpson;
  dx = (b - a) / (n - 1);

  // Dynamische Arrays für x und y Werte
  double *x, *y;

  x = new double[n];
  y = new double[n];

  // Befüllen von x und y = x**2
  x[0] = a;
  y[0] = x[0] * x[0];

  for (int i = 1; i < n; ++i) {
    x[i] = x[i - 1] + dx;
    y[i] = x[i] * x[i];
  }

  // Integration Simpson + Trapez
  itrapez = integration_trapez(x, y, n);
  isimpson = integration_simpson(x, y, n);

  // Ausgabe Ergebnis:
  std::cout << "Ergebnis Trapezregel: " << itrapez << std::endl;
  std::cout << "Ergebnis Simpsonregel: " << isimpson << std::endl;

  return 0;
}
