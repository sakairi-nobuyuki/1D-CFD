#ifndef __BOUNDARY_FOR_ANOTHER_CLASS__
#define __BOUNDARY_FOR_ANOTHER_CLASS__



#include <cstdio>
#include "CFD1D.h"
#include "volume.h"

class CFD1D;
class Volume;
class Boundary {
 private:
  FILE *fp_in, *fp_out;
  char piyo[64], fuga[64], mud[1024];
  int output_freq;
 public:
  Boundary ();
  Boundary (char hoge[64]);
  ~Boundary ();

  double d, A, Rho, U, Q;

  void PipeInletAndVolumeOutlet (Volume *Vol, CFD1D *Pipe);
  void PipeOutletAndVolumeInlet (CFD1D *Pipe, Volume *Vol);

  void Inlet (double RhoV, double PV, double UIn, double RhoP, double PP, int n, double t);
  void Outlet (double RhoV, double PV, double UOut, double RhoP, double PP, int n, double t);


  void Output (int n, double t);
};


#endif
