#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

double F(double m, double a, double as);
double F_m(double m, double a, double as);

int main() {
  double m1, m2;
  double a, as;
  double F1, F2, Fs;
  int max_iter;
  a = 0.2;
  as = 0.15; 

  m1 = 1.0;
  m2 = 1.2;

  std::ofstream ofile;
  ofile.open("plot");
  double x, dx = 2.0 / 100.0;
  for (int i = 0; i < 101; ++i) {
    x = i * dx;
    ofile << x << "," << F(x,a,as) - a/as << std::endl;
  }
  ofile.close();

  
  // Newton
  F2 = F(m2, a, as );
  max_iter = 100;
  while(fabs(F2) > 0.001){
    max_iter --;
    if (max_iter <= 0) break;
    Fs = F_m(m2, a, as);
    m2 = m2 - F2/Fs;
    F2 = F(m2, a, as );
  }
  std::cout << m2 << std::endl;

  // Newton Raphson

  return 0;
}

double F(double m, double a, double as) {
  return (a / as) - (1 / m)  *pow(  (1 + 1 / 6 * (pow(m, 2) - 1)), 3);
}

double F_m(double m, double a, double as) {
  return pow(1 + 1 / 6 * (pow(m, 2) - 1), 2) *
         (1 / pow(m, 2) * (1 + 1 / 6 * (pow(m, 2) - 1)) - 1);
}
