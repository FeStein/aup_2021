// LEAST SQUARE METHODE

#include <math.h>
#include <stdio.h>
#include <iostream>

void tomy(int il, int iu, double *b, double *d, double *a, double *c,
          double *l);
double spline(double *x, double *y, int n, double x1);

int main() {
  int nd = 0;
  double x1, y1;

  FILE *fritz;
  fritz = fopen("xy_data.dat", "r");
  do {
    nd++;
    fscanf(fritz, "%lf %lf\n", &x1, &y1);
  } while (!feof(fritz));
  fclose(fritz);

  double *x, *y;
  x = new double[nd];
  y = new double[nd];

  fritz = fopen("xy_data.dat", "r");
  for (int i = 0; i <= nd - 1; i++) {
    fscanf(fritz, "%lf %lf\n", &x[i], &y[i]);
  }
  fclose(fritz);

  int mm = 1;
  double *x1000, *y1000;
  x1000 = new double[mm];
  y1000 = new double[mm];
  double dx = (x[nd - 1] - x[0]) / (mm - 1);
  for (int i = 0; i <= mm - 1; i++) {
    x1000[i] = x[0] + i * dx;
    y1000[i] = spline(x, y, nd, x1000[i]);
  }

  fritz = fopen("spline.dat", "w");
  for (int i = 0; i <= mm - 1; i++) {
    fprintf(fritz, "%10.5lf %10.5lf\n", x1000[i], y1000[i]);
  }

  delete[] x;
  delete[] y;
  delete[] x1000, delete[] y1000;
}

double spline(double *x, double *y, int n, double x1) {
  double *yss, *h, *a, *b, *c, *d, *A, *B, *D, *RHS;
  double y1;

  yss = new double[n];
  h = new double[n - 1];
  a = new double[n - 1];
  b = new double[n - 1];
  c = new double[n - 1];
  d = new double[n - 1];
  A = new double[n];
  B = new double[n];
  D = new double[n];
  RHS = new double[n];

  // INTERVALLBREITEN
  for (int i = 0; i <= n - 2; i++) {
    h[i] = x[i + 1] - x[i];
  }

  // KOEFFIZIENTEN DES GL-SYSTEMS
  for (int i = 1; i <= n - 2; i++) {
    D[i] = 2. * (h[i - 1] + h[i]);
    B[i] = h[i - 1];
    A[i] = h[i];
    RHS[i] = 6. / h[i] * (y[i + 1] - y[i]) - 6. / h[i - 1] * (y[i] - y[i - 1]);
  }

  A[0] = 0.;
  B[0] = 0.;
  D[0] = 1.;
  RHS[0] = 0.;
  A[n - 1] = 0.;
  B[n - 1] = 0.;
  D[n - 1] = 1.;
  RHS[n - 1] = 0.;

  // LÖSEN DES GL-SYSTEMS
  tomy(0, n - 1, B, D, A, RHS, yss);
  
  for (int i = 0; i <= n - 2; i++) {
    a[i] = 1. / (6. * h[i]) * (yss[i + 1] - yss[i]);
    b[i] = yss[i] / 2.;
    c[i] = (y[i + 1] - y[i]) / h[i] - h[i] / 6. * (yss[i + 1] + 2. * yss[i]);
    d[i] = y[i];
    std::cout << a[i] << " " << b[i] << " " << c[i] << " " << d[i] << " " << std::endl;
  }

  for (int i = 0; i <= n - 2; i++) {
    if ((x1 >= x[i]) && (x1 <= x[i + 1])) {
      y1 = a[i] * pow(x1 - x[i], 3) + b[i] * pow(x1 - x[i], 2) +
           c[i] * (x1 - x[i]) + d[i];
      break;
    }
  }

  delete[] yss;
  delete[] h;
  delete[] a;
  delete[] b;
  delete[] c;
  delete[] d;
  delete[] A;
  delete[] B;
  delete[] D;
  delete[] RHS;

  return (y1);
}

void tomy(int il, int iu, double *b, double *d, double *a, double *c,
          double *l) {
  int m, i;

  for (i = il + 1; i <= iu; i++) {
    d[i] = d[i] - b[i] / d[i - 1] * a[i - 1];
    c[i] = c[i] - b[i] / d[i - 1] * c[i - 1];
  }

  l[iu] = c[iu] / d[iu];
  for (i = 1; i <= (iu - il); i++) {
    m = iu - i;
    l[m] = (c[m] - a[m] * l[m + 1]) / d[m];
  }

  return;
}
