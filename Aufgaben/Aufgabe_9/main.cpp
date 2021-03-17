#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<double> thomas(vector<double> A, vector<double> B, vector<double> C,
                      vector<double> D);

int main() {
  int n = 101;
  double dy;
  dy = 1 / (n - 1);

  //vector<double> RHS(n, 0.0);
  //vector<double> A(n - 1, 0.0);
  //vector<double> B(n, 0.0);
  //vector<double> C(n - 1, 0.0);

  //// RB
  //B.front() = 1.0;
  //B.back() = 1.0;

  //for (int i = 1; i < n - 1; ++i) {
  //  A[i - 1] = 1.0;
  //  B[i] = -2.0;
  //  C[i] = 1.0;
  //  RHS[i] = pow(dy, 2);
  //}

  vector<double> A = {1.0,2.0};
  vector<double> B = {1.0,2.0};
  vector<double> C = {1.0,2.0,3.0};
  vector<double> D = {10.0, 10.0, 10.0};

  vector<double> U = thomas(A, B, C, D);

  ofstream ofile;
  ofile.open("output");
  for (int i = 0; i < n; ++i) {
    ofile << U[i] << endl;
  }
  ofile.close();

  return 0;
}

vector<double> thomas(vector<double> A, vector<double> B, vector<double> C,
                      vector<double> D) {
  int n = B.size();
  // forward subs
  C[0] = C[1] / B[1];
  for (int i = 1; i < n - 1; ++i) {
    C[i] = C[i] / (B[i] - C[i - 1] * A[i]);
  }
  D[0] = D[1] / B[1];
  for (int i = 1; i < n; ++i) {
    D[i] = (D[i] - D[i - 1] * A[i]) / (B[i] - C[i - 1] * A[i]);
  }

  // backwards subs
  vector<double> X(n, 0.0);
  X.back() = D.back();
  for (int i = n - 1; i >= 0; --i) {
    X[i] = D[i] - C[i] * X[i + 1];
  }

  return X;
}
