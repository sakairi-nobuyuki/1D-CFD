//#include <mathimf.h>
#include <math.h>
#include "functions.h"

double sgn (double x) {
  return x/fabs(x);
}

double minmod (double x, double y) {
  //  return sgn(x) * fmax(0, fmin(fabs(x), sgn(x)*y));
    return copysignf(1.0,x) * fmax(0, fmin(fabs(x), copysignf(1,x)*y));
//   if (0 < x*y && fabs (x) < fabs (y)) return x;
//   else if (0 < x*y && fabs (y) < fabs (x)) return y;
//   else return 0;
}
