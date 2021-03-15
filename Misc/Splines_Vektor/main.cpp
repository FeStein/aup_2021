#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

std::vector<double> thomas(std::vector<std::vector<double>> M,
                           std::vector<double> R);

int main() {

  // Read file
  double x, y;
  std::vector<double> X, Y;
  std::ifstream ifile;
  ifile.open("input");
  while (ifile >> x >> y) {
    X.push_back(x);
    Y.push_back(y);
  }
  ifile.close();
  int n = X.size();

  // create LSE for splines
  std::vector<std::vector<double>> M(n, std::vector<double>(n, 0.0));
  std::vector<double> RHS(n, 0.0);
  M.front().front() = 1;
  M.back().back() = 1;

  double hi, hi_1;

  for (int i = 1; i < n - 1; ++i) {
    hi = X[i + 1] - X[i];
    hi_1 = X[i] - X[i - 1];
    M[i][i - 1] = hi_1;
    M[i][i] = 2 * (hi_1 + hi);
    M[i][i+1] = hi; 
    RHS[i] = (6 / hi) * (Y[i + 1] - Y[i]) - (6 / hi_1) * (Y[i] - Y[i-1]);
  }
  
  std::vector<double> YS = thomas(M,RHS);
  std::vector<std::vector<double>> KOEFF(n -1, std::vector<double>(4, 0.0));
  
  // Calculate koeff 
  for (int i = 0; i < n - 1; ++i) {
    hi = X[i + 1] - X[i];
    KOEFF[i][0] = (YS[i +1] - YS[i]) / (6.0 * hi);
    KOEFF[i][1] = YS[i]/2.0;
    KOEFF[i][2] = (Y[i +1] - Y[i]) / hi - (YS[i +1] - YS[i]) / (6.0 * hi) - YS[i] * hi * 0.5;
    KOEFF[i][3] = Y[i];
  }

  std::ofstream ofile;
  ofile.open("output");
  double dx, xi;
  int m = 1001, si, si_max;
  dx = (X.back() - X.front()) / (m-1);
  for (int i = 0; i < m; ++i) {
    x = X.front() + i * dx;
    si = 0;
    while (x > X[si]) {
      si ++ ;
    }
    si --;
    std::cout << si << std::endl;
    break;
    xi = X[si];
    y = 1.0;
    si_max = 0;
    y = KOEFF[si][0] * pow(x - xi, 3)
        + KOEFF[si][1] * pow(x - xi, 2)
        + KOEFF[si][2] * pow(x - xi, 1)
        + KOEFF[si][3];
    ofile << x << "," << y << std::endl;
  }
  ofile.close();

  return 0;
}

// Thomas Algorithmus -> Einfache Vorwärtssubstituion
std::vector<double> thomas(std::vector<std::vector<double>> M,
                           std::vector<double> R) {
  double z, nn;
  int n = M.size();

  // Rekursive Komponentenmodifikation (Vorwärtsdurchlauf)
  M[0][1] = M[0][1] / M[0][0];
  for (int i = 1; i < n - 1; ++i) {
    M[i][i + 1] = M[i][i + 1] / (M[i][i] - M[i - 1][i + 1] * M[i][i - 1]);
  }
  R[0] = R[0] / M[0][0];
  for (int i = 1; i < n; ++i) {
    z = R[i] - R[i - 1] * M[i][i - 1];
    nn = M[i][i] - M[i - 1][i + 1] * M[i][i - 1];
    R[i] = z / nn;
  }

  // Rückwärts Substituion
  std::vector<double> S(n, 0);
  for (int i = n - 2; i >= 0; --i) {
    S[i] = R[i] - M[i][i + 1] * S[i + 1];
  }
  return S;
}
