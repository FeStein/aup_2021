#include "integ_algo.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

double trapez(double ax[], double ay[], int size) {

  double sum = 0;
  for (int i = 0; i < size - 1; i++) {
    sum += (ax[i + 1] - ax[i]) * ((ay[i] + ay[i + 1]) / 2);
  }

  return sum;
}

double simpson(double ax[], double ay[], int size) {
  // check if simpson is possible.
  if (size % 2 != 1 || size < 2) {
    cout << "number of points is even, cant do simpson" << endl;
    return 0;
  } else {
    // step size.
    double h = ax[1] - ax[0];
    double sum = 0;
    for (int i = 0; i < size - 2; i += 2) {
      sum += (h / 3) * (ay[i] + 4 * ay[i + 1] + ay[i + 2]);
    }

    return sum;
  }
}

