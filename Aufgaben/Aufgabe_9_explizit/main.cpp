#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
  double dy;
  int n = 101;

  dy = 1.0 / (n - 1);

  int max_iter = 1000;

  vector<double> U(n, 0.0);
  vector<double> UB(n, 0.0);

  for (int i = 0; i < max_iter; ++i) {
    for (int j = 1; j < n - 1; ++j) {
      U[j] = 0.5 * (pow(dy, 2) + UB[j - 1] + UB[j + 1]);
    }
    UB = U;
  }

  ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    ofile << i*dy << " " << U[i] << endl;
  }
  ofile.close();

  return 0;
}
