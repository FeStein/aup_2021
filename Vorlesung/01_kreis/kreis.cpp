#include <math.h>
#include <iostream>


struct KREIS {
  double xm;
  double ym;
  double R;
};

struct KREIS calculate_kreis(double x1,double y1,double x2,double y2,double x3, double y3)
{
  struct KREIS k;
  //Hilfsvariablen analog zur Herleitung
  double x12q, x12, y12q, y12;
  double x13q, x13, y13q, y13;

  double a,b;

  x12q = x1*x1 - x2*x2;
  y12q = y1*y1 - y2*y2;
  x12 = x1 -x2;
  y12 = y1 -y2;

  x13q = x1*x1 - x3*x3;
  y13q = y1*y1 - y3*y3;
  x13 = x1 -x3;
  y13 = y1 -y3;
  
  a = x12/y12 - x13/y13;
  b = ((x12q + y12q)/(2.*y12)) - ((x13q + y13q) / (2. * y13));

  k.xm = b/a;
  k.ym = (-x12q + 2.*x12 *k.xm - y12q) / (-2. * y12);
  k.R = (x1 - k.xm) * (x1 - k.xm) + (y1 - k.ym) * (y1 - k.ym);
  k.R = sqrt(k.R);

  return k;
}

int main() {
  //Definition kreis struct
  KREIS k;
  
  //Beispielhafte Eingabe der Punkte (5,0);(0,5);(10,5)
  k = calculate_kreis(5,0,0,5,10,5);

  //Ausgabe
  std::cout << k.xm << " " << k.ym << " " << k.R << std::endl;
  return 0;
}
