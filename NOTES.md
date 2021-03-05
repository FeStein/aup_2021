# Notizen

## Programmierideen

* Numerische Integration mit Eingabematrix der Funktion
* Adaptive version von Simpson (mit variablem h)
* File adaptiv einlesen

## Programmbausteine

* Header
```cpp
#include <iostream>
```

* Read File
```cpp
ifstream ifile("input.dat");
int index = 0;
while (!ifile.eof()) {
  ifile >> t_val[index];
  ifile >> f[index];
  index++;
}
```
* Konstante PI
```cpp
M_PI
```


* Definition Array (Statisch, dynamisch etc.)
* for Schleife
* Ausgabe von Werten
* Definition Matrix (Indexierung)
* Lambda Funktionen
* Pow funktion
* Thomas Algorithmus Matrix definition (Generelles wie beim Lösen der Splines
    oä.)
