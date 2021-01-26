#include "integ_algo.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main() {
  // number of points
  int n = 301;
  double arr_x[n];
  double arr_y[n];

  double x0 = -5.;
  double x1 = 7.;

  double h = (x1 - x0) / (n - 1);

  double curr_x;

  // create array of x values.
  for (int i = 0; i < n; i++) {
    curr_x = x0 + i * h;
    arr_x[i] = curr_x;
  }

  // create array of y values.
  for (int i = 0; i < n; i++) {
    arr_y[i] = arr_x[i] * arr_x[i];
  }
  // calc according to trapez.
  double integral = trapez(arr_x, arr_y, n);
  cout << "Trapez: " << integral << endl;

  // calc according to simpson.
  integral = simpson(arr_x, arr_y, n);
  cout << "Simpson: " << integral << endl;

  return 0;
}

