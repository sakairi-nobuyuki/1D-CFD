# 1D-CFD
## Background
This program provides numerical simulation caluculation about dynamic --dynamic means unsteady-- one dimensional compressible fluid dynamics (hereafter called as "1D-CFD").
Often main field of CFD is recgnized as 3-dimensional CFD now a days, however, in some cases on highly complecated fluid system such as piping system,
combustion engine, pulsation on hydrauli system, extremely abstract pictures of pehomena are of great help for people to understand what is happened in the actual system.
In such suite simplified cases, 1D-CFD can provice solutions of simulating the complicated sysytem.

Some commercial applications have achieved this purpose in past score years thanks to the great effort of the developers about such comutational application.
Also great revolutions of user interface for users is the most important aspect of such commercial products showed great success in this field.
On the other side, this program aim to provide rather specialized use for 1D-CFD with taking into account of fluid inertia for calculation.
In some actual experimental cases, fluid pulsation in a fluid manifold or piping system would be a source of troubles.
Therefore person in charge condider to start 1D-CFD simulation.
However if the simulation program he will use does not consider fluid inertia in piping, the numerical simulation never returns such pulsation behaviour.
Furthermore, even if the program can calicurate fluid inertia in pipeing system, proper solver is required for precision and stability of calculation, and usually hard to get it.

To overcome such problems, this program applys state-of-the-art CFD technologies, such as stable compressible fluid dynamics solver and
several kinds of fluid; regardless to liquid or air, the users can fix whichever fluid by setting fluid properties concerning to fluid compressibility.
Even though the flow velosity exceeds sound speed, this program contines stable calculation.

Additionaly, to make the simulation to simulate complete system, some accesories as actuators, valve, booster, or, pumps might be neccesary.
I would add these components time to time in the near future.

- Solver: Compressible fluid mechanics solver with Total Volume Diminishing (hereafter calles as "TVD") on 3-rd order up-wind derivertive.
- Fluid type: Users can input fluid properties, as density, compressibility or other items to simulate liquid or air.

## Specifications

- Solvers
  - 1D-CFD solver
    - Third-order up-wind derivertive flux difference separation type finite volume method with TVD.
    - Tait equation is applied as the constitutive equation of fluid.
    - Appropriate time step control was applied for numerical stability.
  - 0D-CFD solver
    - Simple Euler type forward differential due to its nonliniality.
    - Some special limiter functions for stalbe interconnection between 1D to 0D CFD.
- Development Environment
  - CPU: Intel Core i5
  - RAM: 8GB
  - HDD: 16GB
  - OS:  Mac OS X High Sierra
  - Compiler: g++ 4.2.1
	


## Installation and quick guidance
Users need to compile programs with g++ or other compilers. Intel compiler also hopefully works well however was not confirmed.

### Mac OS/Linux
Once installing g++ to your computer, clone the programs to any directory you want to calculate, as

     $ git clone https://github.com/sakairi-nobuyuki/1D-CFD.git

and, edit `main.cpp` file as what you want to calculrate.

Detail instruction for editing `main.cpp` can be found on Usage section.

After preparing `main.cpp` file, type,

     $ make

will yields, executable `main` file.

Prepare inputfile as `inp.1d.001` by refering the guidance of Usage section of this README, type,

	$ ./main

Then the calculation will start and calculated files are automatically generated in the current directory with ascii type data.
The data structure is described in the Usage section.

### Windows users
Unfortunately this program is not confirmed its function in windows, and also, windows users cannot use `Makefile`
 to compile the program. Windows users should prepare their own compile command such as,

    > g++ -O3 functions.cpp boundary.cpp volume.cpp CFD1D.cpp main.cpp -o main.exe -lm

O3 optimization is recommended.
