#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "CFD1D.h"
#include "volume.h"
#include "boundary.h"

int main () {
  //  CFD1D1Ver Cyl1("cyl1");
  CFD1D Pipe1 ("001"), Pipe2 ("002");
  Volume Vol1 ("001"), Vol2 ("002"), Vol3 ("003");
  Boundary BD1 ("001"), BD2 ("002"), BD3 ("003"), BD4 ("004");
  double dt = 0.0, dt0 = 1.0e-08, t = 0.0, Qtmp = 0.0;
  clock_t start, end;
  int n;
  FILE *fp_out;


  fp_out = fopen ("out.dat", "w");
  printf ("hoge\n\n\n");
  start = clock ();
  Pipe1.InitFlat ();
  //  Pipe1.InitShock ();
  Pipe2.InitFlat ();
  dt = dt0;

  for (n = 0; t < 0.5; n++) {
    Vol1.VolumeToPipeInlet (&BD1, dt);
    BD1.PipeInletAndVolumeOutlet (&Vol1, &Pipe1);

    //    Pipe1.Neumann ();
    Pipe1.InletBoundaryFromVolume (&Vol1, n);
    Pipe1.RoeMUSCL (n, dt);
    Pipe1.OutletBoundaryToVolume (&Vol2, n);

    BD2.PipeOutletAndVolumeInlet (&Pipe1, &Vol2);
    //    Vol2.PipeOutletToVolume (&BD2, dt);

    Vol2.PipeOutletToVolumeToPipeInlet (&BD2, &BD3, dt);

    BD3.PipeInletAndVolumeOutlet (&Vol2, &Pipe2);
    
    Pipe2.InletBoundaryFromVolume (&Vol2, n);
    Pipe2.RoeMUSCL (n, dt);
    Pipe2.OutletBoundaryToVolume (&Vol3, n);
    
    BD4.PipeOutletAndVolumeInlet (&Pipe2, &Vol3);
    Vol3.PipeOutletToVolume (&BD4, dt);



    dt = Pipe1.dt0;
    if (Vol1.dt0 < dt)      dt = Vol1.dt0;
    if (Vol2.dt0 < dt)      dt = Vol2.dt0;
    //    if (dt0 < dt)           dt = dt0;


    if (n % Pipe1.output_freq == 0) {
      Pipe1.Output (n, t);
      Pipe2.Output (n, t);
      printf ("%3.3le\t%3.3le\t%3.3le\t%3.3le\n", Pipe1.dt0, Vol1.dt0, Vol2.dt0, dt);
    }
    if (n % Vol1.output_freq == 0) {
      BD1.Output (n, t);
      BD2.Output (n, t);
      Vol1.Output (n, t);
      Vol2.Output (n, t);

    }


    t += dt;
  }

  end = clock ();
  printf ("calcuration time = %le sec\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC);

  fclose (fp_out);

  return 0;
}
