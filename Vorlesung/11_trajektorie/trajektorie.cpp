#include <fstream>
#include <iostream>
#include <math.h>

double cwert(double Re);

int main() {
  double kappa = 0.3, m = 1., R = 0.105, g = 9.81;
  double x0 = 0., z0 = 0., u0 = 10., v0 = 20.;
  double dt = 0.005, mue = 17.6e-6, rho = 1.225, Re, cw;
  double *x, *z, *xp, *zp, *t;
  double k1x, k2x, k3x, k4x, kx;
  double k1z, k2z, k3z, k4z, kz;
  double k1xp, k2xp, k3xp, k4xp, kxp;
  double k1zp, k2zp, k3zp, k4zp, kzp;

  int n = 1000; // time steps

  x = new double[n];
  z = new double[n];
  t = new double[n];
  xp = new double[n];
  zp = new double[n];

  int i = 0;
  // starting conditions
  x[0] = x0;
  z[0] = z0;
  xp[0] = u0;
  zp[0] = v0;
  t[0] = 0.;

  do {
    // step 1
    Re = sqrt(pow(xp[i], 2) + pow(zp[i], 2)) * rho * 2. * R / mue;
    cw = cwert(Re);
    kappa = cw * rho / 2. * M_PI * R * R;
    k1xp = -kappa / m * xp[i] * sqrt(pow(xp[i], 2) + pow(zp[i], 2));
    k1x = xp[i];
    k1zp = -g - kappa / m * zp[i] * sqrt(pow(xp[i], 2) + pow(zp[i], 2));
    k1z = zp[i];

    // step 2
    Re = sqrt(pow(xp[i] + k1xp * dt / 2., 2) + pow(zp[i] + k1zp * dt / 2., 2)) *
         rho * 2. * R / mue;
    cw = cwert(Re);
    kappa = cw * rho / 2. * M_PI * R * R;
    k2xp =
        -kappa / m * (xp[i] + k1xp * dt / 2.) *
        sqrt(pow(xp[i] + k1xp * dt / 2., 2) + pow(zp[i] + k1zp * dt / 2., 2));
    k2x = (xp[i] + k1xp * dt / 2.);
    k2zp = -g - kappa / m * (zp[i] + k1zp * dt / 2.) *
                    sqrt(pow(xp[i] + k1xp * dt / 2., 2) +
                         pow(zp[i] + k1zp * dt / 2., 2));
    k2z = zp[i] + k1zp * dt / 2.;

    // step 3
    Re = sqrt(pow(xp[i] + k2xp * dt / 2., 2) + pow(zp[i] + k2zp * dt / 2., 2)) *
         rho * 2. * R / mue;
    cw = cwert(Re);
    kappa = cw * rho / 2. * M_PI * R * R;
    k3xp =
        -kappa / m * (xp[i] + k2xp * dt / 2.) *
        sqrt(pow(xp[i] + k2xp * dt / 2., 2) + pow(zp[i] + k2zp * dt / 2., 2));
    k3x = (xp[i] + k2xp * dt / 2.);
    k3zp = -g - kappa / m * (zp[i] + k2zp * dt / 2.) *
                    sqrt(pow(xp[i] + k2xp * dt / 2., 2) +
                         pow(zp[i] + k2zp * dt / 2., 2));
    k3z = zp[i] + k2zp * dt / 2.;

    // step 4
    Re = sqrt(pow(xp[i] + k3xp * dt, 2) + pow(zp[i] + k3zp * dt, 2)) * rho *
         2. * R / mue;
    cw = cwert(Re);
    kappa = cw * rho / 2. * M_PI * R * R;
    k4xp = -kappa / m * (xp[i] + k3xp * dt) *
           sqrt(pow(xp[i] + k3xp * dt, 2) + pow(zp[i] + k3zp * dt, 2));
    k4x = (xp[i] + k3xp * dt);
    k4zp = -g - kappa / m * (zp[i] + k3zp * dt) *
                    sqrt(pow(xp[i] + k3xp * dt, 2) + pow(zp[i] + k3zp * dt, 2));
    k4z = zp[i] + k3zp * dt;

    kx = (k1x + 2. * k2x + 2. * k3x + k4x) / 6.;
    kz = (k1z + 2. * k2z + 2. * k3z + k4z) / 6.;
    kxp = (k1xp + 2. * k2xp + 2. * k3xp + k4xp) / 6.;
    kzp = (k1zp + 2. * k2zp + 2. * k3zp + k4zp) / 6.;

    i++;

    t[i] = t[i - 1] + dt;
    x[i] = x[i - 1] + kx * dt;
    z[i] = z[i - 1] + kz * dt;
    xp[i] = xp[i - 1] + kxp * dt;
    zp[i] = zp[i - 1] + kzp * dt;

  } while ((z[i] > 0.) && (i < n - 1));

  std::ofstream ofile;
  ofile.open("output");
  for (int j = 0; j < i; ++j) {
    ofile << t[j] << " " << x[j] << " " << z[j] << " " << xp[j] << " " << zp[j]
          << std::endl;
  }
  ofile.close();

  delete[] x;
  delete[] z;
  delete[] xp;
  delete[] zp;
  delete[] t;

  return 0;
}

double cwert(double Re) {
  double cw;

  if (Re <= 1000) {
    cw = 24. / Re * (1. + 1. / 6. * pow(Re, 2. / 3.));
  }

  if ((Re > 1000) && (Re <= 3.5e5)) {
    cw = 0.424;
  }

  if (Re > 3.5e5) {
    cw = 0.09;
  }

  return (cw);
}
