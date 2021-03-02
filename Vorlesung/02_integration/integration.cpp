#include <iostream>
// Integration mit Hilfe der Trapezregel
double integration_trapez(double *x, double *y, int n) {
  double Ai, sA;

  sA = 0;
  for (int i = 1; i < n; ++i) {
    Ai = (x[i] - x[i - 1]) * ((y[i] + y[i - 1]) / 2);
    sA += Ai;
  }

  return sA;
}

// Integration mit Hilfe der Simpsonregel
double integration_simpson(double *x, double *y, int n) {
  // check if simpson is possible.
  if (n % 2 != 1 || n < 2) {
    std::cout << "number of points is even, cant do simpson" << std::endl;
    return 0;
  } else {
    // step n.
    double h = x[1] - x[0];
    double sum = 0;
    for (int i = 0; i < n - 2; i += 2) {
      sum += (h / 3) * (y[i] + 4 * y[i + 1] + y[i + 2]);
    }

    return sum;
  }
}
