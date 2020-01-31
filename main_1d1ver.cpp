#include <cstdio>
#include <math.h>
#include "CFD.h"

int main () {
  CFD1D1Ver Cyl1("cyl1");
  double dt = 0.001;
  int n;

  Cyl1.InitShock ();
  for (n = 0; n < 1000; n++) {
    if (n % 100 == 0)
      Cyl1.Output (n, dt);

    Cyl1.Neumann ();
    Cyl1.MUSCL (dt);

  }
  return 0;
}
