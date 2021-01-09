#include <fstream>  // read/write files
#include <iostream> // some terminal stuff
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <string>
using namespace std;

// Definition of circle strucutue, defined by center and radius
struct CIRCLE {
  double xm, ym;
  double R;
};

// Calculation according to lecture
CIRCLE calc_circle(double x1, double y1, double x2, double y2, double x3,
                   double y3) {
  // temp circle structure
  struct CIRCLE circ;
  // factors
  double x12, y12, x12q, y12q, x13, y13, x13q, y13q;
  // results
  double a, b, xm, ym, R;

  // Calculate factors
  x12 = x1 - x2;
  x13 = x1 - x3;

  y12 = y1 - y2;
  y13 = y1 - y3;

  x12q = x1 * x1 - x2 * x2;
  x13q = x1 * x1 - x3 * x3;

  y12q = y1 * y1 - y2 * y2;
  y13q = y1 * y1 - y3 * y3;

  // Calculate results
  a = x12 / y12 - x13 / y13;
  b = (x12q + y12q) / (2. * y12) - (x13q + y13q) / (2. * y13);

  xm = b / a;
  ym = (-x12q + 2. * x12 * xm - y12q) / (-2. * y12);

  R = (x1 - xm) * (x1 - xm) + (y1 - ym) * (y1 - ym);
  R = sqrt(R);

  // Return results
  circ.xm = xm;
  circ.ym = ym;
  circ.R = R;

  return circ;
}

// Main function to calculate xm, ym and R
int main() {
  // initial points
  double x1 = 0., y1 = 0., x2 = 0., y2 = 0., x3 = 0., y3 = 0.;
  // calculated sums
  int number_of_circles;
  // index variables
  CIRCLE circ;

  // Predfine size of vector, is this correct?
  // Size of vector is not changable at runtime
  // Could be done via dynamic array -> propably use smart pointer
  double X[6][3], Y[6][3];

  // ------------------------read from file--------------------------------
  string line;

  ifstream rf("kreis.dat");

  if (rf.is_open()) {
    // get first line for the number of circles
    getline(rf, line);
    number_of_circles = stoi(line);

    // get accodring points
    for (int i = 0; i < number_of_circles; i++) {
      for (int j = 0; j < 3; j++) {
        getline(rf, line);
        // cout << "---" << line << "\n";

        // split line to get the points
        // -> create stringstream
        // -> split stringstream by tab delimiter
        stringstream sst(line);
        string token;

        getline(sst, token, '\t');
        X[i][j] = stod(token);

        getline(sst, token, '\t');
        Y[i][j] = stod(token);
      }
    }

    rf.close();
  }

  else
    cout << "Unable to open input file";

  // ------------------------write to file--------------------------------

  // Write to file
  ofstream wf("RMP.dat");
  if (wf.is_open()) {
    for (int i = 0; i < number_of_circles; i++) {
      // Calculate circle
      circ = calc_circle(X[i][0], Y[i][0], X[i][1], Y[i][1], X[i][2], Y[i][2]);
      wf << circ.xm << "   " << circ.ym << "   " << circ.R << "\n";
    }
    wf.close();
  } else {
    cout << "Unable to open output file";
  }

  // successfully ran program
  return 0;
}
