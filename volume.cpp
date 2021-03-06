#include "volume.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

//////////////////////////////////////////////////
//////////////////////////////////////////////////
////   Constructors & Destructors  
//////////////////////////////////////////////////
//////////////////////////////////////////////////
Volume :: Volume (char hoge[64]) {
  sprintf (piyo, "inp.vol.%s", hoge);
  if ((fp_in = fopen (piyo, "r")) == NULL) {
    printf ("No such file as %s\n", piyo);
    exit (1);
  }

  fscanf (fp_in, "%lf", &d);   fgets (mud, 1024, fp_in);     d *= 1.0e-03;
  fscanf (fp_in, "%lf", &h);   fgets (mud, 1024, fp_in);     h *= 1.0e-03;
  fscanf (fp_in, "%lf", &Rho);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &P);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Gamma); fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &B);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &geometry_type);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &output_freq);    fgets (mud, 1024, fp_in);

  fclose (fp_in);

  if (geometry_type == 0) {
    V = 4.0 / 3.0 * PI * pow (d, 3);
  } else if (geometry_type == 1) {
    V = 0.25 * PI * pow (d, 2) * h;
  } else if (geometry_type == 2) {
    V = pow (h, 3);
  } else {
    printf ("No such geometrical input for %s with %d\n", piyo, geometry_type);
    exit (1);
  }

  C = sqrt (Gamma * (P + B) / Rho);

  printf ("##  %s loaded \n", piyo);
  printf ("Rho:       %le (kg/m3)\n", Rho);
  printf ("P:         %le (Pa)\n", P);
  printf ("V:         %le (m3)\n", V);
  printf ("C:         %le (m3)\n", C);
  printf ("Output Freq: %d\n", output_freq);

  sprintf (piyo, "out.vol.%s", hoge);
  if (fp_out = fopen (piyo, "w")) 
    printf ("output file open for %s\n\n", hoge);

}


Volume::~Volume () {
  fclose (fp_out);

}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//   End Constructors & Destructors
//////////////////////////////////////////////////
//////////////////////////////////////////////////

void Volume::VolumeToPipeInlet (Boundary *Inlet, double dt) {
  C = sqrt (Gamma * (P + B) / Rho);
  Rho -= Inlet->Rho * Inlet->Q / V * dt;
  Omega = pow (C, 2) * Inlet->Rho * Inlet->Q;
  P -=  Omega * dt;
  //  if (1.0e-06 < fabs (Omega)) dt0 = 0.5 / Omega;
  //  else dt0 = 100000.0;
  dt0 = returnOmega ();
}
void Volume::PipeOutletToVolume (Boundary *Outlet, double dt) {
  C = sqrt (Gamma * (P + B) / Rho);
  Rho += Outlet->Rho * Outlet->Q / V * dt;
  Omega = pow (C, 2) * Outlet->Rho * Outlet->Q / V;
  P += Omega * dt;
  //  if (1.0e-06 < fabs (Omega)) dt0 = 0.5 / Omega;
  //  else dt0 = 100000.0;
  dt0 = returnOmega ();
}

void Volume::PipeOutletToVolumeToPipeInlet (Boundary *Outlet, Boundary *Inlet, double dt) {
  C = sqrt (Gamma * (P + B) / Rho);
  Rho += (Outlet->Rho * Outlet->Q - Inlet->Rho * Inlet->Q) / V * dt;
  Omega = pow (C, 2) * (Outlet->Rho * Outlet->Q - Inlet->Rho * Inlet->Q) / V;
  P += Omega * dt;
  //  if (1.0e-06 < fabs (Omega)) dt0 = 0.5 / Omega;
  //  else dt0 = 100000.0;
  dt0 = returnOmega ();
}



double Volume::returnOmega () {
  double dt0;

  if (1.0e-06 < fabs (Omega)) dt0 = 1.0 / Omega;
  else dt0 = 100000.0;
  return dt0;
}


void Volume::AirInlet1 (double Q, int n, double dt, double t) {
  Rho -= Rho * Q / V * dt;
  P -= Q / V * Gamma * P * dt;

  if (n % output_freq == 0)
    fprintf (fp_out, "%le\t%le\t%le\n", t, Rho, P);
}

void Volume::AirOutlet1 (double Q, int n, double dt, double t) {
  Rho += Rho * Q / V * dt;
  P += Q / V * Gamma * P * dt;

  if (n % output_freq == 0)
    fprintf (fp_out, "%le\t%le\t%le\n", t, Rho, P);
}

void Volume::Output (int n, double t) {
  fprintf (fp_out, "%le\t%le\t%le\t%le\n", t, Rho, P, C);



}
