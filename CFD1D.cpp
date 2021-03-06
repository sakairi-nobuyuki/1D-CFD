#include "cfd1d.h"
#include <math.h>
#include <cstdio>
#include <stdlib.h>

#define PI 3.14159265

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
////   Constructors  & Destructors
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
CFD1D::CFD1D (){}
CFD1D::CFD1D (char hoge[64]) {
//CFD1D::CFD1D (char *) {
  sprintf (piyo, "inp.1d.%s", hoge);
  if ((fp_in = fopen (piyo, "r")) == NULL) {
    printf ("No such file as %s(>_<;)\n", piyo);
    exit (1);
  }
  fscanf (fp_in, "%d", &LL);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &L);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &d);   fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Rho0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &U0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &P0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Gamma); fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &B); fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Co);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &b);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &kappa);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Epsilon);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &output_freq);  fgets (mud, 1024, fp_in);

  d *= 1.0e-03;
  A = 0.25 * PI * pow (d, 2);

  dx = L / (double)LL;
  kappa = 1.0/3.0;
  b = (3.0 - kappa) / (1.0 - kappa);

  printf ("##%s loaded\n", piyo);
  printf ("Size of stencil:   %d (-)\n", LL);
  printf ("Length of stencil: %lf (m)\n", L);
  printf ("Rho0:              %lf (kg/m3)\n", Rho0);
  printf ("U0:                %lf (m/s)\n", U0);
  printf ("P0:                %le (Pa)\n", P0);
  printf ("Gamma:             %lf (-)\n", Gamma);
  printf ("B    :             %le (Pa)\n", B);
  printf ("Courant Number:    %lf (-)\n", Co);
  printf ("Epsilon:           %lf (-)\n", Epsilon);
  printf ("dx:                %le (m)\n", dx);
  printf ("kappa              %le (-)\n", kappa);
  printf ("b:                 %le (-)\n", b);
  printf ("output_frequcncy:  %d\n\n", output_freq);
  fclose (fp_in);

  Rho = new double [LL];
  RhoU = new double [LL];
  RhoE = new double [LL];
  RhoF = new double [LL];
  RhoUF = new double [LL];
  RhoEF = new double [LL];
  U = new double [LL];
  P = new double [LL];
  C = new double [LL];
  H = new double [LL];
  Rhotmp = new double [LL];
  RhoUtmp = new double [LL];
  RhoEtmp = new double [LL];
  RhoR = new double [LL];
  RhoL = new double [LL];
  RhoUR = new double [LL];
  RhoUL = new double [LL];
  RhoER = new double [LL];
  RhoEL = new double [LL];
  UL = new double [LL];
  UR = new double [LL];
  HL = new double [LL];
  HR = new double [LL];
  PL = new double [LL];
  PR = new double [LL];
  SlopeTmp = new double [LL];
  F = new double [LL];
  DeltaPlus = new double [LL];
  DeltaMinus = new double [LL];


  printf ("memory allocated for %s\n", hoge);
  sprintf (piyo, "%s", hoge);
  printf ("\n");
}


CFD1D::~CFD1D () {
  delete [] Rho;
  delete [] RhoU;
  delete [] RhoE;
  delete [] U;
  delete [] P;
  delete [] C;
  delete [] H;
  delete [] Rhotmp;
  delete [] RhoUtmp;
  delete [] RhoEtmp;
  delete [] RhoR;
  delete [] RhoL;
  delete [] RhoUR;
  delete [] RhoUL;
  delete [] RhoER;
  delete [] RhoEL;
  delete [] RhoF;
  delete [] UL;
  delete [] UR;
  delete [] HL;
  delete [] SlopeTmp;
  delete [] HR;
  delete [] PL;
  delete [] PR;
  delete [] RhoUF;
  delete [] RhoEF;
  delete [] F;
  delete [] DeltaPlus;
  delete [] DeltaMinus;
  printf ("memory freed for %s\n", piyo);
  printf ("\n");
}

CFD1D1Ver::CFD1D1Ver (){}
CFD1D1Ver::CFD1D1Ver (char hoge[64]) {
  //CFD1D1Ver::CFD1D1Ver (char *) {
  sprintf (piyo, "inp.1d.%s", hoge);
  if ((fp_in = fopen (piyo, "r")) == NULL) {
    printf ("No such file as %s(>_<;)\n", piyo);
    exit (1);
  }
  fscanf (fp_in, "%d", &LL);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &L);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Co);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &b);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &kappa);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Epsilon);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &output_freq);  fgets (mud, 1024, fp_in);

  dx = L / (double)LL;
  kappa = 1.0/3.0;
  b = (3.0 - kappa) / (1.0 - kappa);

  printf ("##%s loaded\n", piyo);
  printf ("Size of stencil:   %d (n)\n", LL);
  printf ("Length of stencil: %lf (m)\n", L);
  printf ("Courant Number:    %lf (-)\n", Co);
  printf ("Epsilon:           %lf (-)\n", Epsilon);
  printf ("dx:                %le (m)\n", dx);
  printf ("kappa              %le (-)\n", kappa);
  printf ("b:                 %le (-)\n", b);
  printf ("output_frequcncy:  %d\n", output_freq);
  fclose (fp_in);

  Q = new double [LL];
  F = new double [LL];
  U = new double [LL];
  DeltaPlus = new double [LL];
  DeltaMinus = new double [LL];
  QR = new double [LL];
  QL = new double [LL];
  FluxPlus = new double [LL];
  FluxMinus = new double [LL];
  Qtmp = new double [LL];

  printf ("memory allocated for %s\n", piyo);

  sprintf (piyo, "%s", hoge);
  //  printf ("%s\n", piyo);

//   sprintf (piyo, "out.1d.%s", hoge);
//   if (fp_out = fopen (piyo, "w")) {
//     printf ("open output file for %s as %s\n", hoge, piyo);
//   } else {
//     printf ("could not open output file for %s as %s(>_<;)\n", hoge, piyo);
//     exit (1);
//  }
  printf ("\n");


}


CFD1D1Ver::~CFD1D1Ver () {
  //  fclose (fp_out);
  //  printf ("close output file for %s\n", piyo);

  delete [] Q;
  delete [] F;
  delete [] U;
  delete [] DeltaPlus;
  delete [] DeltaMinus;
  delete [] QR;
  delete [] QL;
  delete [] FluxPlus;
  delete [] FluxMinus;
  delete [] Qtmp;

  printf ("memory freed for %s\n", piyo);
  printf ("\n");
}



CFD1D_IBM::CFD1D_IBM (){}
CFD1D_IBM::CFD1D_IBM (char hoge[64]) {
  //CFD1D1Ver::CFD1D1Ver (char *) {
  sprintf (piyo, "inp.1d.ibm.%s", hoge);
  if ((fp_in = fopen (piyo, "r")) == NULL) {
    printf ("No such file as %s(>_<;)\n", piyo);
    exit (1);
  }

  fscanf (fp_in, "%d", &LL);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &L);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &d);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Rho0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &U0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &P0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Gamma); fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Co);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &b);  fgets (mud, 1024, fp_in);
  //  fscanf (fp_in, "%lf", &kappa);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &Epsilon);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%d", &output_freq);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &MaskX0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &MaskU0);  fgets (mud, 1024, fp_in);
  fscanf (fp_in, "%lf", &MaskOmega);  fgets (mud, 1024, fp_in);

  dx = L / (double)LL;
  kappa = 1.0/3.0;
  b = (3.0 - kappa) / (1.0 - kappa);

  A = 0.25 * PI * pow (d * 1.0e-3, 2);

  printf ("##%s loaded\n", piyo);
  printf ("Size of stencil:   %d (-)\n", LL);
  printf ("Length of stencil: %lf (m)\n", L);
  printf ("Diameter         : %lf (mm)\n", d);
  printf ("Cross sec. area  : %lf (m2)\n", A);
  printf ("Rho0:              %lf (kg/m3)\n", Rho0);
  printf ("U0:                %lf (m/s)\n", U0);
  printf ("P0:                %lf (Pa)\n", P0);
  printf ("Gamma:             %lf (-)\n", Gamma);
  printf ("Courant Number:    %lf (-)\n", Co);
  printf ("Epsilon:           %lf (-)\n", Epsilon);
  printf ("dx:                %le (m)\n", dx);
  printf ("kappa              %le (-)\n", kappa);
  printf ("b:                 %le (-)\n", b);
  printf ("output_frequcncy:  %d\n\n", output_freq);
  printf ("MaskU0:                %lf (m/s)\n", MaskU0);
  printf ("MaskX0:                %lf (m)\n", MaskX0);
  printf ("Omega:                %lf (rad/s)\n", MaskOmega);
  fclose (fp_in);

  Rho = new double [LL];
  RhoU = new double [LL];
  RhoE = new double [LL];
  RhoF = new double [LL];
  RhoUF = new double [LL];
  RhoEF = new double [LL];
  U = new double [LL];
  P = new double [LL];
  C = new double [LL];
  H = new double [LL];
  Rhotmp = new double [LL];
  RhoUtmp = new double [LL];
  RhoEtmp = new double [LL];
  RhoR = new double [LL];
  RhoL = new double [LL];
  RhoUR = new double [LL];
  RhoUL = new double [LL];
  RhoER = new double [LL];
  RhoEL = new double [LL];
  UL = new double [LL];
  UR = new double [LL];
  HL = new double [LL];
  HR = new double [LL];
  PL = new double [LL];
  PR = new double [LL];
  SlopeTmp = new double [LL];
  F = new double [LL];
  DeltaPlus = new double [LL];
  DeltaMinus = new double [LL];


  printf ("memory allocated for %s\n", hoge);
  sprintf (piyo, "%s", hoge);
  printf ("\n");

}


CFD1D_IBM::~CFD1D_IBM () {
  delete [] Rho;
  delete [] RhoU;
  delete [] RhoE;
  delete [] U;
  delete [] P;
  delete [] C;
  delete [] H;
  delete [] Rhotmp;
  delete [] RhoUtmp;
  delete [] RhoEtmp;
  delete [] RhoR;
  delete [] RhoL;
  delete [] RhoUR;
  delete [] RhoUL;
  delete [] RhoER;
  delete [] RhoEL;
  delete [] RhoF;
  delete [] UL;
  delete [] UR;
  delete [] HL;
  delete [] SlopeTmp;
  delete [] HR;
  delete [] PL;
  delete [] PR;
  delete [] RhoUF;
  delete [] RhoEF;
  delete [] F;
  delete [] DeltaPlus;
  delete [] DeltaMinus;
  printf ("memory freed for %s\n", piyo);
  printf ("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////    End Constructors & Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void CFD1D::RoeMUSCL (int n, double dt) {
  int i;
  double MaxPhaseSpeed;


  //  Unknown Vars.
  for (i = 0; i < LL; i++)  RhoU[i] = Rho[i] * U[i];
  for (i = 0; i < LL; i++)  RhoE[i] = (P[i] + B) / (Gamma - 1.0) + 0.5 * Rho[i] * pow (U[i], 2);
  //  for (i = 0; i < LL; i++)  H[i] = RhoE[i] / Rho[i] + P[i];
  for (i = 0; i < LL; i++)  H[i] = Gamma / (Gamma - 1.0) * (P[i] + B) / Rho[i] + 0.5*pow(U[i],2);
  for (i = 0; i < LL; i++)  F[i] = 0.0;
  for (i = 3; i < LL-2; i++)  {
    //    C[i] = sqrt (fabs (Gamma * P[i] / Rho[i]));
    C[i] = sqrt( (Gamma - 1.0) * (H[i]));
    if (isnan (C[i])) {
      printf ("Sound Speed nan on %s n = %d i = %d U = %3.3le H = %3.3le P = %3.3le\n", piyo, n, i, U[i], H[i], P[i]);
      Output (n, n*dt);
      exit (1);
    }
  }
  //  printf ("%le\n", C[i]);
  //  for (i = 0; i < LL; i++)  C[i] = Gamma * P[i] / Rho[i];

  //  CFL condition
  cx = dt / dx;

  MaxPhaseSpeed = 0.0;
  for (i = 3; i < LL-2; i++) 
    MaxPhaseSpeed = fmax (MaxPhaseSpeed, (fmax (fabs (U[i] - C[i]), fabs (U[i] + C[i]))));
  //  cx = Co / MaxPhaseSpeed;
  //  printf ("%le\n", MaxPhaseSpeed);
      
  //  cx = Co * dt / dx;
  ///  if (n % output_freq == 0) printf ("dt = %lf\n", 1.0/MaxPhaseSpeed);



  //   Outlet Side i+1/2
  QLeftRightOutlet ();   //  Obtain RhoR, RhoL, RhoUR, RhoL, RhoER, RhoEL
  //  nprintf ("hoge\n");
  for (i = 2; i < LL-2; i++) {
    RoeAverage (i);
    RightDiagonalMatrix ();
    LeftDiagonalMatrix ();
    AbsLambda ();
    AbsJacobiA ();

    RhoURtmp = RhoR[i] * UR[i];    RhoULtmp = RhoL[i] * UL[i];
    //    RhoERtmp = (Gamma - 1.0) * PR[i] + 0.5 * RhoR[i] * pow (UR[i], 2);
    //    RhoELtmp = (Gamma - 1.0) * PL[i] + 0.5 * RhoL[i] * pow (UL[i], 2);
    RhoERtmp = PR[i] / (Gamma - 1.0) + 0.5 * RhoR[i] * pow (UR[i], 2);
    RhoELtmp = PL[i] / (Gamma - 1.0) + 0.5 * RhoL[i] * pow (UL[i], 2);
    //    HRtmp = Gamma / (Gamma - 1.0) * PR[i] / RhoR[i] + 0.5 * pow(UR[i], 2);
    //    HLtmp = Gamma / (Gamma - 1.0) * PL[i] / RhoL[i] + 0.5 * pow(UL[i], 2);
    //    RhoOutF = 0.5 * (RhoUR[i] + RhoUL[i]
    RhoOutF = 0.5 * (RhoURtmp + RhoULtmp
		     - (JacobiA[0][0] * (RhoR[i] - RhoL[i]) 
			+ JacobiA[0][1] * (RhoURtmp - RhoULtmp) 
			+ JacobiA[0][2] * (RhoERtmp - RhoELtmp)));
			//			+ JacobiA[0][1] * (RhoUR[i] - RhoUL[i]) 
			//			+ JacobiA[0][2] * (RhoER[i] - RhoEL[i])));
    RhoUOutF = 0.5 * (RhoR[i] * pow (UR[i], 2) + PR[i] 
		      + RhoL[i] * pow (UL[i], 2) + PL[i]
		     - (JacobiA[1][0] * (RhoR[i] - RhoL[i]) 
			+ JacobiA[1][1] * (RhoURtmp - RhoULtmp) 
			+ JacobiA[1][2] * (RhoERtmp - RhoELtmp)));
    //    RhoEOutF = 0.5 * (RhoURtmp * HRtmp
    //		      + RhoULtmp * HLtmp
    RhoEOutF = 0.5 * (RhoURtmp * HR[i]
		      + RhoULtmp * HL[i]
		      - (JacobiA[2][0] * (RhoR[i] - RhoL[i])
			 + JacobiA[2][1] * (RhoUR[i] - RhoUL[i])
			 + JacobiA[2][2] * (RhoER[i] - RhoEL[i]))); 
//     for (ii = 0; ii < 3; ii++) {
//       for (kk = 0; kk < 3; kk++)  printf ("%lf\t ", JacobiA[ii][kk]);
//       printf ("\n");
//     }
//       printf ("\n");

    RoeAverage (i-1);
    RightDiagonalMatrix ();
    LeftDiagonalMatrix ();
    AbsLambda ();
    AbsJacobiA ();

    RhoURtmp = RhoR[i-1] * UR[i-1];    RhoULtmp = RhoL[i-1] * UL[i-1];
    //    RhoERtmp = (Gamma - 1.0) * PR[i-1] + 0.5 * RhoR[i-1] * pow (UR[i-1], 2);
    //    RhoELtmp = (Gamma - 1.0) * PL[i-1] + 0.5 * RhoL[i-1] * pow (UL[i-1], 2);
    RhoERtmp = PR[i-1] / (Gamma - 1.0) + 0.5 * RhoR[i-1] * pow (UR[i-1], 2);
    RhoELtmp = PL[i-1] / (Gamma - 1.0) + 0.5 * RhoL[i-1] * pow (UL[i-1], 2);

    RhoInF = 0.5 * (RhoURtmp + RhoULtmp
		      - (JacobiA[0][0] * (RhoR[i-1] - RhoL[i-1])
			 + JacobiA[0][1] * (RhoURtmp - RhoULtmp)
			 + JacobiA[0][2] * (RhoERtmp - RhoELtmp))); 
    RhoUInF = 0.5 * (RhoR[i-1] * pow (UR[i-1], 2) + PR[i-1] 
		     + RhoL[i-1] * pow (UL[i-1], 2) + PL[i-1]
		      - (JacobiA[1][0] * (RhoR[i-1] - RhoL[i-1])
			 + JacobiA[1][1] * (RhoURtmp - RhoULtmp)
			 + JacobiA[1][2] * (RhoERtmp - RhoELtmp))); 
    RhoEInF = 0.5 * (RhoURtmp * HR[i-1]
		      + RhoULtmp * HL[i-1]
		      - (JacobiA[2][0] * (RhoR[i-1] - RhoL[i-1])
			 + JacobiA[2][1] * (RhoURtmp - RhoULtmp)
			 + JacobiA[2][2] * (RhoERtmp - RhoELtmp))); 
    RhoF[i]  = RhoOutF - RhoInF;
    RhoUF[i] = RhoUOutF - RhoUInF;
    RhoEF[i] = RhoEOutF - RhoEInF;

    //    printf ("RhoF = %lf, RhoUF = %lf, RhoEF = %lf\n", RhoF[i], RhoUF[i], RhoEF[i]);
    //    printf ("RhoER = %lf, RhoEL = %lf\n", RhoER[i], RhoEL[i]);
    //    printf ("A11 = %le, A12 = %le, A13=%le\n", JacobiA[0][0], JacobiA[0][1], JacobiA[0][2]);
  }

  for (i = 2; i < LL-2; i++)    Rhotmp[i] = Rho[i] - cx * RhoF[i]; 
  for (i = 2; i < LL-2; i++)    RhoUtmp[i] = RhoU[i] - cx * RhoUF[i]; 
  for (i = 2; i < LL-2; i++)    RhoEtmp[i] = RhoE[i] - cx * RhoEF[i]; 

  for (i = 2; i < LL-2; i++)    Rho[i] = Rhotmp[i];
  for (i = 2; i < LL-2; i++)    RhoU[i] = RhoUtmp[i];
  for (i = 2; i < LL-2; i++)    RhoE[i] = RhoEtmp[i];

  for (i = 0; i < LL; i++)  U[i] = RhoU[i] / Rho[i];
  for (i = 0; i < LL; i++)  P[i] = (RhoE[i] - 0.5*Rho[i]*pow(U[i],2)) * (Gamma - 1.0) - B;

  dt0 = Co * dx / MaxPhaseSpeed;  
  //  dt = Co * dx / MaxPhaseSpeed;  
  //  return dt;
}





inline void CFD1D::AbsJacobiA () {
    int j, k, l;
    //  int j, k, l;

    //  Compose Jacobi Matrix
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) JacobiAtmp[j][k] = 0.0;
    }
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) JacobiA[j][k] = 0.0;

    }
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) {
	for (l = 0; l < 3; l++) JacobiAtmp[j][k] += DiagR[j][l] * Lambda[l][k];
      }
    }
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) {
	for (l = 0; l < 3; l++) JacobiA[j][k] += JacobiAtmp[j][l] * DiagL[l][k];
      }
    }


//     printf ("subroutine A11 = %le, A12 = %le, A13=%le\n", JacobiAtmp[0][0], JacobiAtmp[0][1], JacobiAtmp[0][2]);
//     printf ("subroutine A21 = %le, A22 = %le, A23=%le\n", JacobiAtmp[1][0], JacobiAtmp[1][1], JacobiAtmp[1][2]);
//     printf ("subroutine A31 = %le, A22 = %le, A33=%le\n", JacobiAtmp[2][0], JacobiAtmp[2][1], JacobiAtmp[2][2]);
//    for (ii = 0; ii < 3; ii++) {
//      for (kk = 0; kk < 3; kk++)  printf ("%lf\t ", JacobiA[ii][kk]);
//      printf ("\n");
//    }
//      printf ("\n");

}

inline void CFD1D::AbsLambda () {
    Lambda[0][0] = fabs (RoeU - RoeC);   Lambda[0][1] = 0.0;           Lambda[0][2] = 0.0;
    Lambda[1][0] = 0.0;                  Lambda[1][1] = fabs (RoeU);   Lambda[1][2] = 0.0;
    Lambda[2][0] = 0.0;                  Lambda[2][1] = 0.0;           Lambda[2][2] = fabs (RoeU + RoeC);
}

inline void CFD1D::RoeAverage (int i) {
    RoeRho = sqrt (RhoR[i] * RhoL[i]);
    RoeU   = (sqrt(RhoR[i])*UR[i] + sqrt(RhoL[i])*UL[i]) / (sqrt(RhoL[i]) + sqrt(RhoR[i]));
    RoeH   = (sqrt(RhoR[i])*HR[i] + sqrt(RhoL[i])*HL[i]) / (sqrt(RhoL[i]) + sqrt(RhoR[i]));
    RoeC   = sqrt(fabs((Gamma - 1.0) * (RoeH - 0.5 * pow (RoeU, 2))));
    //    printf ("RoeRho = %lf, RoeU = %lf, RoeH = %lf, RoeC = %lf\n", RoeRho, RoeU, RoeH, RoeC);
}

inline void CFD1D::RightDiagonalMatrix () {
//     int ii, kk; 

  //    for (j = 0; j < 3; j++)
  //      DiagR[j][0] = 1.0;
  DiagR[0][0] = 1.0;   DiagR[0][1] = 1.0;  DiagR[0][2] = 1.0;
  DiagR[1][0] = RoeU - RoeC;   DiagR[1][1] = RoeU;   DiagR[1][2] = RoeU + RoeC;
  DiagR[2][0] = RoeH - RoeC * RoeU;
  DiagR[2][1] = 0.5 * pow (RoeU, 2);
  DiagR[2][2] = RoeH + RoeC * RoeU;

//    for (ii = 0; ii < 3; ii++) {
//      for (kk = 0; kk < 3; kk++)  printf ("%lf\t ", DiagR[ii][kk]);
//      printf ("\n");
//    }
//     printf ("\n");

}

inline void CFD1D::LeftDiagonalMatrix () {
    //  Compose Left Diagonal Matrix for F|i-1/2
    Eta1 = (Gamma - 1.0) / pow(RoeC, 2);
    Eta2 = 0.5 * Eta1 * pow (RoeU, 2);
    DiagL[0][0] = 0.5 * (Eta2 + RoeU / RoeC);
    DiagL[0][1] =  -0.5 * (Eta1 * RoeU + 1.0 / RoeC);
    DiagL[0][2] = 0.5 * Eta1;
    DiagL[1][0] = 1.0 - Eta2;
    DiagL[1][1] = Eta1 * RoeU;
    DiagL[1][2] = -Eta1;
    DiagL[2][0] = 0.5 * (Eta2 - RoeU / RoeC);
    DiagL[2][1] =  -0.5 * (Eta1 * RoeU - 1.0 / RoeC);
    DiagL[2][2] = 0.5 * Eta1;
}

inline void CFD1D::QLeftRightOutlet () {
  int i;

  //   Rho|i+1/2 --> RhoR, RhoL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (Rho[i+1] - Rho[i], b*(Rho[i] - Rho[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (Rho[i] - Rho[i-1], b*(Rho[i+1] - Rho[i]));
    //    printf ("DeltaPlus = %lf\n", DeltaPlus);

  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    RhoL[i] = Rho[i] + 0.25*s * ((1-kappa*s)* DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 
  }  /// 2.8462E-02
     //   for (i = 1; i < LL-1; i++) 
     //     SlopeTmp[i] = (2.0 * DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
     //   for (i = 1; i < LL-1; i++) 
     //     RhoL[i] = Rho[i] + 0.25* SlopeTmp[i] * ((1-kappa*s)* DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 

  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    RhoR[i] = Rho[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 
  }


  //   RhoU|i+1/2 --> RhoUR, RhoUL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (RhoU[i+1] - RhoU[i], b*(RhoU[i] - RhoU[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (RhoU[i] - RhoU[i-1], b*(RhoU[i+1] - RhoU[i]));
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    RhoUL[i] = RhoU[i] + 0.25*s * ((1-kappa*s) * DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 

  }
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    RhoUR[i] = RhoU[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 

  }



  //   RhoE|i+1/2 --> RhoER, RhoEL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (RhoE[i+1] - RhoE[i], b*(RhoE[i] - RhoE[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (RhoE[i] - RhoE[i-1], b*(RhoE[i+1] - RhoE[i]));
  for (i = 1; i < LL-1; i++) {
    s = (2.0* DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    RhoEL[i] = RhoE[i] + 0.25*s * ((1-kappa*s) * DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 
    //    printf ("s = %lf, RhoEL = %lf\n", s, RhoEL[i]);
  }
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    RhoER[i] = RhoE[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 
  }



  //   U|i+1/2 --> UR, UL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (U[i+1] - U[i], b*(U[i] - U[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (U[i] - U[i-1], b*(U[i+1] - U[i]));
  for (i = 1; i < LL-1; i++) {
    s = (2.0* DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    UL[i] = U[i] + 0.25*s * ((1-kappa*s) * DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 
  }
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    UR[i] = U[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 
  }


  //   H|i+1/2 --> HR, HL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (H[i+1] - H[i], b*(H[i] - H[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (H[i] - H[i-1], b*(H[i+1] - H[i]));
  for (i = 1; i < LL-1; i++) {
    s = (2.0* DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    HL[i] = H[i] + 0.25*s * ((1-kappa*s) * DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 
  }
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    HR[i] = H[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 
  }
  //   P|i+1/2 --> PR, PL
  for (i = 1; i < LL-1; i++) 
    DeltaPlus[i]  = minmod (P[i+1] - P[i], b*(P[i] - P[i-1]));
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (P[i] - P[i-1], b*(P[i+1] - P[i]));
  for (i = 1; i < LL-1; i++) {
    s = (2.0* DeltaPlus[i] * DeltaMinus[i] + Epsilon) / (pow (DeltaPlus[i], 2) + pow (DeltaMinus[i], 2) + Epsilon);
    PL[i] = P[i] + 0.25*s * ((1-kappa*s) * DeltaPlus[i] + (1+kappa*s) * DeltaMinus[i]); 
  }
  for (i = 1; i < LL-1; i++) {
    s = (2.0 * DeltaPlus[i+1] * DeltaMinus[i+1] + Epsilon) / (pow (DeltaPlus[i+1], 2) + pow (DeltaMinus[i+1], 2) + Epsilon);
    PR[i] = P[i+1] - 0.25*s * ((1-kappa*s) * DeltaPlus[i+1] + (1+kappa*s) * DeltaMinus[i+1]); 
  }
  //    for (i = 0; i < LL; i++)  printf ("HR = %lf, HL = %lf\n", HL[i], HR[i]);

  //    if (fp_out = fopen ("hoge.dat", "w")) printf ("hoge.dat open\n");
//    fp_out = fopen ("hoge.dat", "w");
//    for (i = 0; i < LL; i++)
//      fprintf (fp_out, "%le, %le, %le, %le\n", RhoL[i], RhoR[i], UL[i], UR[i]);
//    fclose (fp_out);

}

void CFD1D::InitFlat () {
  int i;

  for (i = 0; i < LL; i++) Rho[i] = Rho0;
  for (i = 0; i < LL; i++) U[i] = U0;
  for (i = 0; i < LL; i++) P[i] = P0;
  for (i = 0; i < LL; i++) RhoU[i] = Rho[i] * U[i];
  for (i = 0; i < LL; i++) RhoE[i] =  P[i] / (Gamma - 1.0) + 0.5 * Rho[i] * pow (U[i], 2);
}

void CFD1D::InitShock () {
  int i;


  //  for (i = 0; i < LL/2; i++) Rho[i] = 8.0*Rho0;
  for (i = 0; i < LL/2; i++) Rho[i] = Rho0;
  for (i = LL/2; i < LL; i++) Rho[i] = Rho0;
  //  for (i = 0; i < LL; i++) printf ("Rho=%lf\n", Rho[i]);
  for (i = 0; i < LL/2; i++) P[i] = 10.0*P0;
  for (i = LL/2; i < LL; i++) P[i] = P0;
  for (i = 0; i < LL; i++) U[i] = 0.0;
  //  for (i = 0; i < LL; i++)    printf ("%d, %lf\n", i, Cyl1.Rho[i]);

  for (i = 0; i < LL; i++) RhoU[i] = Rho[i] * U[i];
  //  for (i = 0; i < LL; i++) RhoE[i] = Rho[i] * (Gamma - 1.0) * P[i] + 0.5 * Rho[i] * pow (U[i], 2);
  for (i = 0; i < LL; i++) RhoE[i] =  P[i] / (Gamma - 1.0) + 0.5 * Rho[i] * pow (U[i], 2);
  //  for (i = 0; i < LL; i++) H[i] = RhoE[i] / Rho[i] - P[i];
  //  for (i = 0; i < LL; i++)  printf ("RhoU = %lf, RhoE = %lf, H = %lf\n", RhoU[i], RhoE[i], H[i]);
}


void CFD1D::InletBoundaryFromVolume (Volume *Vol, int n) {
  if (P[0] + 0.5 * Rho[0] * pow (U[0], 2) < Vol->P) {
    //    for (i = 2; 0 <= i; i--) Rho[i] = Vol->Rho;
    for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
    for (i = 2; 0 <= i; i--) U[i] = U[i+1];
    for (i = 2; 0 <= i; i--) P[i] = Vol->P;
  } else {
    for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
    for (i = 2; 0 <= i; i--) U[i] = U[i+1];
    //    for (i = 2; 0 <= i; i--) P[i] = Vol->P;
    for (i = 2; 0 <= i; i--) P[i] = Vol->P - 0.5 * Rho[i] * pow (U[i], 2);
  }
}

void CFD1D::OutletBoundaryToVolume (Volume *Vol, int n) {
  if (P[LL-1] < Vol->P) {
    //    for (i = LL-2; i < LL; i++) Rho[i] = Vol->Rho;
    for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
    for (i = LL-2; i < LL; i++) U[i] = U[i-1];
    for (i = LL-2; i < LL; i++) P[i] = Vol->P;
  } else {
    for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
    for (i = LL-2; i < LL; i++) U[i] = U[i-1];
    for (i = LL-2; i < LL; i++) P[i] = Vol->P - 0.5 * Rho[i] * pow (U[i], 2);
  }
}


void CFD1D::InterfaceToVolume (Volume VolUp, Volume VolDown, int n) {

}


void CFD1D::xxInterfaceToVolume (double RhoIn, double UIn, double PIn, double RhoOut, double UOut, double POut, int n) {
  int i = 0;

  //  Inlet
  RhoB[0] = RhoIn;
  UB[0] = U[3];
  PB[0] = PIn;

  RhoUB[0] = RhoB[0] * UB[0];
  RhoEB[0] = PB[0] / (Gamma - 1.0) + 0.5 * RhoB[0] * pow (UB[0], 2);

  printf ("Mass = %lf\n", RhoB[0]);
  printf ("Momentum = %lf\n", RhoUB[0]);
  printf ("Energy = %lf\n\n", RhoEB[0]);

  RhoBtmp[0] = RhoB[0] + cx * (RhoIn * UB[0] - Rho[3] * U[3]);    //   freezed boundary condition
  RhoUBtmp[0] = RhoUB[0] + cx * (RhoIn *   pow (UB[0], 2) + PIn - Rho[3] * pow (U[3], 2) - P[3]);
  RhoEBtmp[0] = RhoEB[0] + cx * (UB[0] * (Gamma / (Gamma - 1.0) * PIn   + 0.5 * RhoIn   * pow (UB[0], 2)) -
				 U[3]  * (Gamma / (Gamma - 1.0) * P[3]  + 0.5 * Rho[3] * pow (U[3], 2)));
  printf ("RhoIn = %lf, PIn = %lf\n", RhoIn, PIn);
  printf ("Mass Flux = %lf\n", cx*(RhoIn * UB[0] - Rho[3] * U[3]));
  printf ("Momentum Flux = %lf\n", cx*(RhoIn *   pow (UB[0], 2) + PIn - Rho[3] * pow (U[3], 2) - P[3]));
  printf ("Energy Flux = %lf\n\n", cx*(UB[0] * (Gamma / (Gamma - 1.0) * PIn   + 0.5 * RhoIn   * pow (UB[0], 2)) -
				     U[3]  * (Gamma / (Gamma - 1.0) * P[3]  + 0.5 * Rho[3] * pow (U[3], 2)) ));

  UBtmp[0] = RhoUBtmp[0] / RhoBtmp[0];
  PBtmp[0] = (Gamma - 1.0) * (RhoEBtmp[0] - 0.5 * RhoB[0] * pow (UBtmp[0], 2));
  
  for (i = 0; i < 3; i++)  {
    Rho[i] = RhoBtmp[0];
    U[i] = UBtmp[0];
    P[i] = PBtmp[0];
  }

  RhoB[0] = RhoBtmp[0];  UB[0] = UBtmp[0];    PB[0] = PBtmp[0];

  printf ("%dth iteration, cx = %le\n", n, cx);
  printf ("Rho0 = %le, Rho1 = %le, Rho2 = %le\n", RhoB[0], RhoB[1], RhoB[2]);  
  printf ("U0 = %le, U1 = %le, U2 = %le\n", UB[0], UB[1], UB[2]);
  printf ("P0 = %le, P1 = %le, P2 = %le\n", PB[0], PB[1], PB[2]);

  //  Outlet
  RhoB[2] = RhoBtmp[LL-4];
  UB[2] = U[LL-4];
  PB[2] = PBtmp[LL-4];

  RhoUB[2] = RhoB[2] * UB[2];
  RhoEB[2] = PB[2] / (Gamma - 1.0) + 0.5 * RhoB[2] * pow (UB[2], 2);

  RhoBtmp[2] = RhoB[2] + cx * (RhoIn *  UB[2] - Rho[LL-4] * U[LL-4]);    //   freezed boundary condition
  RhoUBtmp[2] = RhoUB[2] - cx * (RhoIn *   pow (UB[2], 2) + PIn   - Rho[LL-4] * pow (UB[LL-4], 2) - PB[LL-4]);
  RhoEBtmp[2] = RhoEB[2] + cx * (UB[0] * (Gamma / (Gamma - 1.0) * PIn   + 0.5 * RhoIn   * pow (UB[2], 2)) -   // 
				 UB[2] * (Gamma / (Gamma - 1.0) * PB[LL-4] + 0.5 * Rho[LL-4] * pow (U[LL-4], 2)));

  UBtmp[2] = RhoUBtmp[2] / RhoBtmp[2];
  PBtmp[2] = (Gamma - 1.0) * (RhoEBtmp[2] - 0.5 * RhoB[2] * pow (UBtmp[2], 2));
  
  for (i = 0; i < 3; i++)  {
    Rho[i] = RhoBtmp[2];
    U[i] = UBtmp[2];
    P[i] = PBtmp[2];
  }

//   if (P[LL-1] < POut)
//     UBtmp = -1.0 * sqrt (2.0 / RhoOut * (POut - P[LL-1]));
//   else if (POut < P[LL-1])
//     UBtmp = sqrt (2.0 / Rho[LL-1] * (P[LL-1] - POut));
//   else 
//     UBtmp = 0.0;

//   UBtmp = 0.0;
//   UBtmp = U[LL-4];
//   Rhotmp = Rho[LL-1] - cx * (RhoOut * UBtmp - RhoU[LL-4]);
//   RhoUtmp = RhoU[LL-1] - cx * (RhoOut * pow (UBtmp, 2) + POut - Rho[LL-4] * pow (U[LL-4], 2) - P[LL-4]);
//   RhoEtmp = RhoE[LL-1] - cx * (RhoOut * UOut * (Gamma / (Gamma - 1.0) * POut / RhoOut + 0.5 * pow (UBtmp, 2)) - 
// 			    Rho[LL-4] * U[LL-4] * (Gamma / (Gamma - 1.0) * P[LL-4] / Rho[LL-4] + 0.5 * pow (U[LL-4], 2)));
//   Utmp = RhoUtmp / Rhotmp;
//   Ptmp = (Gamma - 1.0) * (RhoEtmp - 0.5 * pow (Utmp, 2));
  
//   for (i = LL-3; i < LL; i++) Rho[i] = Rhotmp;
//   for (i = LL-3; i < LL; i++) U[i] = Utmp;
//  for (i = LL-3; i < LL; i++) P[i] = Ptmp;
}



void CFD1D::Neumann () {
  for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  for (i = 2; 0 <= i; i--) RhoU[i] = RhoU[i+1];
  for (i = LL-2; i < LL; i++) RhoU[i] = RhoU[i-1];
  for (i = 2; 0 <= i; i--) RhoE[i] = RhoE[i+1];
  for (i = LL-2; i < LL; i++) RhoE[i] = RhoE[i-1];

   for (i = 2; 0 <= i; i--) U[i] = U[i+1];
   for (i = LL-2; i < LL; i++) U[i] = U[i-1];
   for (i = 2; 0 <= i; i--) P[i] = P[i+1];
   for (i = LL-2; i < LL; i++) P[i] = P[i-1];
}


void CFD1D::InletOutletBoundary (double Qin, double Qout) {
  double Uin, Uout;

  Uin = Qin / A;
  Uout = Qout / A;
  //  printf ("Q U inout %lf, %lf, %lf, %lf\n", Qin, Qout, Uin, Uout);

  for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  //  for (i = 2; 0 <= i; i--) RhoU[i] = RhoU[i+1];
  //  for (i = LL-2; i < LL; i++) RhoU[i] = RhoU[i-1];
  //  for (i = 2; 0 <= i; i--) RhoE[i] = RhoE[i+1];
  //  for (i = LL-2; i < LL; i++) RhoE[i] = RhoE[i-1];

  for (i = 2; 0 <= i; i--) U[i] = Uin;
  for (i = LL-2; i < LL; i++) U[i] = Uout;
  for (i = 2; 0 <= i; i--) P[i] = P[i+1];
  for (i = LL-2; i < LL; i++) P[i] = P[i-1];
  //  printf ("in inout boundary of Cyl Uin=%lf, Uout=%lf\n", Uin, Uout);
}


void CFD1D::Output (int n, double t) {
  int i;

  sprintf (fuga, "out.1d.%s.%03d", piyo, n);
  if (fp_out = fopen (fuga, "w")) printf ("open %s for %dth output\n", fuga, n/1000);
  else exit (1);

  fprintf (fp_out, "#t = %lf\n", t);
  for (i = 0; i < LL; i++)
    fprintf (fp_out, "%le\t%le\t%le\t%le\t%le\t%le\n", i*dx, Rho[i], U[i], P[i], fabs(U[i] / C[i]), C[i]);
  //  for (i = 0; i < LL; i++)    printf ("%d, %lf\n", i, Rho[i]);
  fclose (fp_out);
  //  printf ("hoge\n");
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//   1Dimensional 1Variable 
////////////////////////////////////////////////////////////////////////////////////////////////////
void CFD1D1Ver::MUSCL (double dt) {
  cx = Co * dt / dx;

//   printf ("Courant Number:    %lf\n", Co);
//   printf ("Epsilon:           %lf\n", Epsilon);
//   printf ("dx:                %le\n", dx);
//   printf ("kappa              %le\n", kappa);
//   printf ("b:                 %le\n", b);
//   printf ("\n");

  //  Intermediate Variable Delta+ & Delta-
  for (i = 1; i < LL-1; i++) {     //  Q|i+1 - Q|i --> Delta+|
    DeltaPlus[i]  = minmod (Q[i+1]-Q[i], b*(Q[i]-Q[i-1]));
    //    printf ("%le\n", DeltaPlus[i]);
  }
  for (i = 1; i < LL-1; i++)
    DeltaMinus[i] = minmod (Q[i]-Q[i-1], b*(Q[i+1]-Q[i]));
 //  Flux Outlet Side of a Control Volume i.e. Q|i+1/2
  ////  Left Side Q of Outlet Side of a Control Volume i.e. QL|i+1/2
  for (i = 1; i < LL-1; i++) {
    s = (2.0*DeltaPlus[i]*DeltaMinus[i] + Epsilon) / (pow(DeltaPlus[i], 2) + pow(DeltaMinus[i], 2) + Epsilon);
    QL[i] = Q[i] + 0.25*s * ((1-kappa*s)*DeltaPlus[i] + (1+kappa*s)*DeltaMinus[i]); 
  }
  ////  Right Side Q of Outlet Side of a Control Volume i.e. QR|i+1/2
  for (i = 1; i < LL-1; i++) {
    s = (2.0*DeltaPlus[i+1]*DeltaMinus[i+1] + Epsilon) / (pow(DeltaPlus[i+1], 2) + pow(DeltaMinus[i+1], 2) + Epsilon);
    QR[i] = Q[i+1] - 0.25*s * ((1-kappa*s)*DeltaPlus[i+1] + (1+kappa*s)*DeltaMinus[i+1]); 
  }
  ////  Outlet Side Flux of a Control Volume i.e. FR|i+1/2
  for (i = 0; i < LL-1; i++) 
    FluxPlus[i] = 0.5*(U[i+1] + U[i]) * (QR[i] + QL[i]) - fabs(0.5*(U[i+1] + U[i])) * (QR[i] - QL[i]);

  //  Flux Inlet Side of a Control Volume i.e. Q|i-1/2
  ////  Left Side Flux of Outlet Side of a Control Volume i.e. QL|i+1/2
  for (i = 1; i < LL-1; i++) {
    s = (2.0*DeltaPlus[i-1]*DeltaMinus[i-1] + Epsilon) / (pow(DeltaPlus[i-1], 2) + pow(DeltaMinus[i-1], 2) + Epsilon);
    QL[i] = Q[i-1] + 0.25*s * ((1-kappa*s)*DeltaPlus[i-1] + (1+kappa*s)*DeltaMinus[i-1]); 
  }
  ////  Right Side Flux of Outlet Side of a Control Volume i.e. QR|i+1/2
  for (i = 1; i < LL-1; i++) {
    s = (2.0*DeltaPlus[i]*DeltaMinus[i] + Epsilon) / (pow(DeltaPlus[i], 2) + pow(DeltaMinus[i], 2) + Epsilon);
    QR[i] = Q[i] - 0.25*s * ((1-kappa*s)*DeltaPlus[i] + (1+kappa*s)*DeltaMinus[i]); 
  }
  ////  Inlet Side Flux of a Control Volume i.e. FR|i+1/2
  for (i = 1; i < LL-1; i++) 
    FluxMinus[i] = 0.5*(U[i] + U[i-1]) * (QR[i] + QL[i]) - fabs(0.5*(U[i] + U[i-1])) * (QR[i] - QL[i]);

  //  Time Evolution
  for (i = 1; i < LL-1; i++) {
    Qtmp[i] = Q[i] - cx * (FluxPlus[i] - FluxMinus[i]);
  }
  for (i = 1; i < LL-1; i++) 
    Q[i] = Qtmp[i];
}



void CIP (double dt) {

  
}




void CFD1D1Ver::Neumann () {
  for (i = 2; 0 <= i; i--) Q[i] = Q[i+1];
  for (i = LL-2; i < LL; i++) Q[i] = Q[i-1];
}

void CFD1D1Ver::InitShock () {
  int i;

  for (i = 0; i < LL/2; i++) 
    Q[i] = 1.0;
  for (i = LL/2+1; i < LL; i++) 
    Q[i] = 0.0;
  //  for (i = 0; i < LL; i++)  printf ("%d, %lf\n", i, Q[i]);
  for (i = 0; i < LL; i++) U[i] = 1.0;

}


void CFD1D1Ver::Output (int n, double dt) {

  int i;

  sprintf (fuga, "out.1d.%s.%03d", piyo, n);
  if (fp_out = fopen (fuga, "w")) printf ("open %s for %dth output\n", fuga, n);
  else exit (1);

  fprintf (fp_out, "#t = %lf\n", n * dt);
  for (i = 0; i < LL; i++)
    fprintf (fp_out, "%le\t%le\n", i*dx, Q[i]);

  fclose (fp_out);

}




//////////////////////////////////////////////////
//           Immersed Boundary Method           //
//            with Ghost-Cesll Method           //
//////////////////////////////////////////////////

void CFD1D_IBM::MaskMoveSine (double t) {
  //   MaskX = 0.5 * MaskX0 * (1.0 + sin (MaskOmega * t));
  //   MaskU = 0.5 * MaskX0 * MaskOmega * cos (MaskOmega * t);

  //  printf ("hoge\n");

  MaskX = 0.45 * L * (1.0 + sin (MaskOmega * t));
  MaskU = 0.45 * L * MaskOmega * cos (MaskOmega * t);

  i_ghost_cell = (int) floor (MaskX);

  for (i = 0; i < i_ghost_cell; i++) U[i] = 0.5 * (MaskU + U[i+1]);
  for (i = 0; i < i_ghost_cell; i++) Rho[i] = Rho[i_ghost_cell + 1];
  for (i = 0; i < i_ghost_cell; i++) P[i] = P[i_ghost_cell + 1];
  //  GhostCellX = GhostCellU0 * sin (Omega * t) + GhostCellX0;  
  //  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  //  for (i = LL-2; i < LL; i++) P[i] = P[i-1];
  //  for (i = LL-2; i < LL; i++) U[i] = U[i-1];

  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  for (i = LL-2; i < LL; i++) P[i] = P[i-1];
  for (i = LL-2; i < LL; i++) U[i] = 0.0;

  //  GhostCellU = GhostCellU * Omega * cos (Omega * t);

}


void CFD1D_IBM::MaskMoveSineWithScvpt (double Qin, double Qout, double t) {
  double Uin, Uout;

  Uin = Qin / A;
  Uout = Qout / A;

  for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
  for (i = 2; 0 <= i; i--) U[i] = Uin;
  for (i = 2; 0 <= i; i--) P[i] = P[i+1];

  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  for (i = LL-2; i < LL; i++) P[i] = P[i-1];
  if (120.0 < Theta && Theta < 240.0) {
    for (i = LL-2; i < LL; i++) U[i] = Uout;
  } else {
    for (i = LL-2; i < LL; i++) U[i] = 0.0;
  }


  MaskX = 0.45 * L * (1.0 + sin (MaskOmega * t));
  MaskU = 0.45 * L * MaskOmega * cos (MaskOmega * t);

  i_ghost_cell = (int) floor (MaskX);

  for (i = 0; i < i_ghost_cell; i++) U[i] = 0.5 * (MaskU + U[i+1]);
  for (i = 0; i < i_ghost_cell; i++) Rho[i] = Rho[i_ghost_cell + 1];
  for (i = 0; i < i_ghost_cell; i++) P[i] = P[i_ghost_cell + 1];


}


void CFD1D_IBM::EngCylBoundary (double Qin, double Qout, double MaskX, double MaskU, double Theta, double t) {
  double Uin, Uout;

  Uin = Qin / A;
  Uout = Qout / A;

  //  for (i = 2; 0 <= i; i--) Rho[i] = Rho[i+1];
  //  for (i = 2; 0 <= i; i--) U[i] = Uin;
  //  for (i = 2; 0 <= i; i--) P[i] = P[i+1];

  //  ExhV side flow
  for (i = LL-2; i < LL; i++) Rho[i] = Rho[i-1];
  for (i = LL-2; i < LL; i++) P[i] = P[i-1];
  if (120.0 / 360.0 * PI< Theta && Theta < 240.0/ 360.0 * PI) {
    for (i = LL-2; i < LL; i++) U[i] = Uout;
  } else {
    for (i = LL-2; i < LL; i++) U[i] = 0.0;
  }


  //    MaskX = 0.45 * L * (1.0 + sin (MaskOmega * t));
  //  MaskU = 0.45 * L * MaskOmega * cos (MaskOmega * t);

  // Piston and scv pt. side flow
  //  i_ghost_cell = LL * (int) floor (MaskX / L);
  i_ghost_cell = (int) floor (MaskX / L * LL);

  //  for (i = i_ghost_cell; i_ghost_cell - 3 < i; i--) U[i] = 0.5 * (MaskU + U[i+1]);
  //  for (i = i_ghost_cell; i_ghost_cell - 3 < i; i--) Rho[i] = Rho[i_ghost_cell + 1];
  //  for (i = i_ghost_cell; i_ghost_cell - 3 < i; i--) P[i] = P[i_ghost_cell + 1];
  //  if (160.0 / 360.0 * PI < Theta && Theta < 200.0 / 360.0 * PI) 
    for (i = 0; i < i_ghost_cell; i++) U[i] = 0.5 * (MaskU + U[i+1]) + Uin;
    //  else
    //    for (i = 0; i < i_ghost_cell; i++) U[i] = 0.5 * (MaskU + U[i+1]);

  for (i = 0; i < i_ghost_cell; i++) Rho[i] = Rho[i_ghost_cell + 1];
  for (i = 0; i < i_ghost_cell; i++) P[i] = P[i_ghost_cell + 1];

  //  printf ("i_ghost_cell %d, mask pos. %lf\n", i_ghost_cell, MaskX);
}


void CFD1D_IBM::detectGhostCell (double X) {
  double Ptmp;

  i_ghost_cell = (int) floor (X);

  U[i_ghost_cell + 1] = GhostCellU;  U[i_ghost_cell] = GhostCellU;  U[i_ghost_cell - 1] = GhostCellU;
  P[i_ghost_cell + 1] = P[i_ghost_cell + 2];  P[i_ghost_cell] = P[i_ghost_cell + 2];  P[i_ghost_cell - 1] = P[i_ghost_cell + 2];
  Rho[i_ghost_cell + 1] = Rho[i_ghost_cell + 2];  Rho[i_ghost_cell] = Rho[i_ghost_cell + 2];  Rho[i_ghost_cell - 1] = Rho[i_ghost_cell + 2];
}


void CFD1D_IBM::Output (int n, double t) {
  int i;

  printf ("%lf\t%lf\t%lf\t%d\n", t, MaskX, MaskU, i_ghost_cell);
  

  sprintf (fuga, "out.1d.ibm.%s.%03d", piyo, n);
  if (fp_out = fopen (fuga, "w")) printf ("open %s for %dth output\n", fuga, n/1000);
  else exit (1);

  fprintf (fp_out, "#t = %lf\n", t);
  for (i = 0; i < LL; i++)
    fprintf (fp_out, "%le\t%le\t%le\t%le\t%le\t%le\n", i*dx, Rho[i], U[i], P[i], fabs(U[i] / C[i]), C[i]);
  //  for (i = 0; i < LL; i++)    printf ("%d, %lf\n", i, Rho[i]);
  fclose (fp_out);
  //  printf ("hoge\n");
}
