#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include "boundary.h"

#define PI 3.14159265

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//   Constructors & Destructors
//////////////////////////////////////////////////
//////////////////////////////////////////////////
Boundary::Boundary (char hoge[64]) {
  sprintf (piyo, "inp.bd.%s", hoge);
  if ((fp_in = fopen (piyo, "r")) == NULL) {
    printf ("No such file as %s\n", piyo);
    exit (1);
  }

  fscanf (fp_in, "%lf", &d);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &U);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &output_freq);    fgets (mud, 1024, fp_in);

  fclose (fp_in);

  d *= 1.0e-03;
  A = 0.25 * PI * pow (d, 2);
  Q = A * U;

  printf ("##  %s loaded \n", piyo);
  printf ("d:   %le (m)\n", d);
  printf ("A:   %le (m2)\n", A);
  printf ("U:   %le (m/s)\n", U);
  printf ("Q:   %le (m3/s)\n", Q);
  printf ("Output Freq: %d\n", output_freq);

  sprintf (piyo, "out.bd.%s", hoge);
  if (fp_out = fopen (piyo, "w")) 
    printf ("output file open for %s\n\n", hoge);

}

Boundary::~Boundary () {
  fclose (fp_out);
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//   End Constructors & Destructors
//////////////////////////////////////////////////
//////////////////////////////////////////////////

void Boundary::PipeInletAndVolumeOutlet (Volume *Vol, CFD1D *Pipe) {
  U = Pipe->U[0] * Pipe->A / A;
  Q = U * A;
  Rho = Pipe->Rho[0];
}
void Boundary::PipeOutletAndVolumeInlet (CFD1D *Pipe, Volume *Vol) {
  U = Pipe->U[Pipe->LL-1] * Pipe->A / A;
  Q = U * A;
  Rho = Pipe->Rho[Pipe->LL-1];
}



void Boundary::Output (int n, double t) {
  fprintf (fp_out, "%le\t%le\t%le\n", t, U, Q);
}


void Boundary::Inlet (double RhoV, double PV, double UIn,  double RhoP, double PP, int n, double t) {
  if (PP < PV) 
    //    U = sqrt (2.0 / RhoV * (PV - PP));
    U = UIn;
  else
    //U = -sqrt (2.0 / RhoP * (PP - PV));
    U = UIn;
  Q = U * A;

  //    printf ("Inlet: PVol = %le, Q = %le, U = %le, UIn = %le\n", PV, Q, U, UIn);

  if (n % output_freq == 0) {
    //    printf ("Inlet: PVol = %le, PPipe = %le, U = %le, UIn = %le\n", PV, PV, U, UIn);
    fprintf (fp_out, "%le\t%le\t%le\n", t, U, Q);
  }

}


void Boundary::Outlet (double RhoV, double PV, double UOut, double RhoP, double PP, int n, double t) {
  if (PP < PV) 
    //    U = -sqrt (2.0 / RhoV * (PV - PP));
    U = UOut;
  else
    //    U = sqrt (2.0 / RhoP * (PP - PV));
    U  = UOut;
  Q = U * A;

  //printf ("Outlet: PVol = %le, Q = %le, U = %le, UOut = %le\n", PV, Q, U, UOut);

  if (n % output_freq == 0) {
    //printf ("Outlet: PVol = %le, PPipe = %le, U = %le, UOut = %le\n", PV, PV, U, UOut);
    fprintf (fp_out, "%le\t%le\t%le\n", t, U, Q);
  }

}
