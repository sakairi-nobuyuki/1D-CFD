#ifndef __VOLUME_FOR_ANOTHER_CLASS__
#define __VOLUME_FOR_ANOTHER_CLASS__


#include <cstdio>
#include "boundary.h"

class Boundary;
class Volume {
 private:
  FILE *fp_in, *fp_out;
  char piyo[64], fuga[64], mud[1024];

 public:
  Volume ();
  Volume (char hoge[64]);
  ~Volume ();

  int geometry_type, fluid_type, output_freq;
  double Rho, V, P,
    d, h, A, Gamma, K, C, B, dt0, Omega;

  void VolumeToPipeInlet (Boundary *Inlet, double dt);
  void PipeOutletToVolume (Boundary *Outlet, double dt);
  void PipeOutletToVolumeToPipeInlet (Boundary *Outlet, Boundary *Inlet, double dt);
  double returnOmega ();

  void AirInlet1 (double Q, int n, double dt, double t);
  void AirOutlet1 (double Q, int n, double dt, double t);

  void Output (int n, double t);
};


#endif
