#ifndef __CFD1D_FOR_ANOTHER_CLASS__
#define __CFD1D_FOR_ANOTHER_CLASS__


#include "functions.h"
#include "boundary.h"
#include "volume.h"
#include <cstdio>

class Volume;
class CFD1D {
 protected:
  int i;
  char piyo[64], fuga[64], mud[1024];
  FILE *fp_in, *fp_out;
  //  double *Rho, *RhoU, *RhoE, *RhoF, *RhoUF, *RhoEF,
  //    *U, *H, *C, *P, Rho0, U0, P0,
  double *RhoU, *RhoE, *RhoF, *RhoUF, *RhoEF,
    *H, *C, Rho0, U0, P0,
    *Rhotmp, *RhoUtmp, *RhoEtmp,
    *RhoR, *RhoL, *RhoUR, *RhoUL, *RhoEL, *RhoER, 
    *UR, *UL, *HR, *HL, *PR, *PL, *SlopeTmp, 
    RoeRho, RoeU, RoeH, RoeC, Eta1, Eta2,
    RhoOutF, RhoUOutF, RhoEOutF, RhoInF, RhoUInF, RhoEInF, RhoURtmp, RhoULtmp, RhoERtmp, RhoELtmp, HRtmp, HLtmp, 
    DiagR[3][3], DiagL[3][3], Lambda[3][3], JacobiA[3][3], JacobiAtmp[3][3],
    RhoBtmp[3], UBtmp[3], PBtmp[3], RhoB[3], UB[3], PB[3], RhoUB[3], RhoUBtmp[3], RhoEBtmp[3], RhoEB[3], 
    //  var. for 1 var. convection eq.
    *Q, *Qtmp, *F, *DeltaPlus, *DeltaMinus, *QR, *QL, *FluxPlus, *FluxMinus,
    L, Co, s, kappa, b, Epsilon, dx, cx;
  inline void QLeftRightOutlet ();
  //  inline void QLeftRightInlet ();
  inline void RoeAverage (int i);
  inline void RightDiagonalMatrix ();
  inline void LeftDiagonalMatrix ();
  inline void AbsLambda ();
  inline void AbsJacobiA ();
 public:
  CFD1D ();
  CFD1D (char hoge[64]);
  ~CFD1D ();

  int output_freq, LL;
  double Gamma, B, *Rho, *U, *P, d, A, dt0;

  void RoeMUSCL (int n, double dt);
  void InitShock ();
  void InitFlat ();
  void Neumann ();
  void InletOutletBoundary (double Qin, double Qout);
  void InletBoundaryFromVolume (Volume *Vol, int n);
  void OutletBoundaryToVolume (Volume *Vol, int n);
  void InterfaceToVolume (Volume VolUp, Volume VolDown, int n);
  void xInterfaceToVolume (double RhoIn, double UIn, double PIn, double RhoOut, double UOut, double POut, int n);
  void xxInterfaceToVolume (double RhoIn, double UIn, double PIn, double RhoOut, double UOut, double POut, int n);
  void Output (int n, double t);
};

class CFD1D1Ver : public CFD1D {
 public:
  CFD1D1Ver ();
  CFD1D1Ver (char hoge[64]);
  ~CFD1D1Ver ();
  void MUSCL (double dt);
  void CIP (double dt); 
  void Neumann ();
  void InitShock ();
  void InitFlat ();
  void Output (int n, double dt);
};


class CFD1D_IBM : public CFD1D {
 protected:
  char piyo[64], fuga[64], mud[1024];
  int i, i_ghost_cell;
  FILE *fp_in, *fp_out;
  double MaskX, MaskU, 
    MaskX0, MaskU0, MaskOmega, MaskTheta,
    MaskRho, MaskP,
    GhostCellX, GhostCellU,
    GhostCellX0, GhostCellU0;  
 public:
  double Theta;
  CFD1D_IBM ();
  CFD1D_IBM (char hoge[64]);
  ~CFD1D_IBM ();


  int output_freq;

  //  void MaskMoveSine (double Omega, double t);
  void MaskMoveSine (double t);
  void MaskMoveSineWithScvpt (double Qin, double Qout, double t);
  //  void EngCylBoundary (double Qin, double Qout, double Theta, double t);
  void EngCylBoundary (double Qin, double Qout, double MaskX, double MaskU, double Theta, double t);
  void detectGhostCell (double X);
  void Output (int n, double t);
};



#endif
