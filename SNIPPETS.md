# Snippets for Exam

## Standard header 
```cpp
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;
```

## Definition of a Structure
```cpp
struct KREIS {
  double xm;
  double ym;
  double R;
};

struct Kreis k;

// get Item via 
k.xm
```

## Definition of a function
```cpp
double function_name(x, y) {
  x = x + y;
  return x;
}
```

## for loop
```cpp
for (int i = 0; i < i; ++i) {
  do_stuff(); 
}
```

## do while loop
```cpp
n = 1;
do {
  n++; 
  do_something();
} while (n < 10);
```

## if then else statement
```cpp
if (n>1) {
  do_something_1();
}
else{
  do_something_2();
}
```

## array done by raw pointer
```cpp
double *ARR;
ARR = new double[10];
```

## read file line by line
```cpp
std::ifstream ifile;

// File Länge checken
int n;
double x, y;
ifile.open("xy_data.dat");
n = 0;
while (ifile >> x >> y) {
    n += 1;
}
ifile.close();

double *xarr, *yarr;

xarr = new double[n];
yarr = new double[n];

// Daten Einlesen
ifile.open("xy_data.dat");
for (int i = 0; i < n; ++i) {
    ifile >> xarr[i] >> yarr[i];
}
ifile.close();
```

## write matrix x[n], y[n] to file 
```cpp
std::ofstream ofile;
ofile.open("output");

for (int i = 0; i < no; ++i) {
    ofile << XO[i] << " " << YO[i] << std::endl;
}
ofile.close();
```

