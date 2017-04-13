#pragma once
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>

#include "Topology.h"
#include "data_structure.h"

class Parameters
{
private:
	FLOAT _T	;				// Time span of the simulation
	FLOAT _dt	;				// Time-step of the numerical scheme
	FLOAT _theta;				// theta in the numerical scheme
	FLOAT _tau;				// tau safety factor for stability in time stepping
	FLOAT _L[3]	;				// Geometery of the simulation cube
	FLOAT _dX[3];
	FLOAT _g	;			// gravitational constant
	FLOAT _nu	;			// kinmetic viscosity
	FLOAT _gamma_t;		// wind constant
	FLOAT _gamma_b;		// friction constant
	FLOAT _u_a;			// wind speed in x direction
	FLOAT _v_a;			// wind speed in y direction
	FLOAT _height;  // free surface water height
	FLOAT _block_size_2d;
	FLOAT _output_flag;
	FLOAT _precipitation;
protected:
	int _N[3]	;				// Number of cells in xyz directions
	int _NGlobal[3]	;				// Number of cells in xyz directions
public:
	Parameters();						// constructor
	Parameters(int argc, char * argv[]);
	Parameters(int argc, char * argv[], Topology& topology);
	~Parameters();						// destructor
	void parse(int argc, char * argv[]); 	// method to parse inputs and set the parameters
	void print_parameters(); 			// print parameters to the consule

	FLOAT get_sim_time() const;
	FLOAT GetCubeLength(int dim) const;
	FLOAT get_time_step() const;
	FLOAT get_tau() const;
	int   get_num_cells(int dim) const;
	FLOAT get_dxdydz(int dim) const;
	FLOAT get_vis() const;
	FLOAT get_gamma_b() const;
	FLOAT get_gamma_t() const;
	FLOAT get_viscosity() const;
	FLOAT get_theta() const;
	FLOAT get_g() const;
	FLOAT get_u_a() const;
	FLOAT get_v_a() const;
	FLOAT GetHeight() const;
	FLOAT GetBlockSize2d() const;		// just used for the petsc parallel 2d solver in case of well distributed domains
	int	  GetOutputFlag() const;
	FLOAT GetPrecipitation() const;

	Topology& topology;
};
