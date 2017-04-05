#pragma once
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include "Topology.h"

class Parameters
{
private:
	float _T	;				// Time span of the simulation
	float _dt	;				// Time-step of the numerical scheme
	float _theta;				// theta in the numerical scheme
	float _L[3]	;				// Geometery of the simulation cube
	float _dX[3];
	float _g	;			// gravitational constant
	float _nu	;			// kinmetic viscosity
	float _gamma_t;		// wind constant
	float _gamma_b;		// friction constant
	float _u_a;			// wind speed in x direction
	float _v_a;			// wind speed in y direction
	float _height;  // free surface water height
	float _block_size_2d;
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

	float get_sim_time() const;
	float GetCubeLength(int dim) const;
	float get_time_step() const;
	int   get_num_cells(int dim) const;
	float get_dxdydz(int dim) const;
	float get_vis() const;
	float get_gamma_b() const;
	float get_gamma_t() const;
	float get_viscosity() const;
	float get_theta() const;
	float get_g() const;
	float get_u_a() const;
	float get_v_a() const;
	float GetHeight() const;
	float GetBlockSize2d() const;		// just used for the petsc parallel 2d solver in case of well distributed domains

	Topology& topology;
};
