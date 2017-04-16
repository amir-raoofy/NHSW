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
	
	// simulation parameters and default values //
	FLOAT _T				=3.0;			// Time span of the simulation (s)
	FLOAT _dt				=0.01;			// Time-step of the numerical schemen (s)
	FLOAT _tau				=0.5;			// tau safety factor for stability in time stepping ( tau << 1)
	FLOAT _theta			=0.5;			// theta in the numerical scheme (0.5< \theta <=1)
	FLOAT _L[3]				={10, 10, 12};	// Geometery of the simulation cube
	FLOAT _height   		=10.0;  		// free surface water height (m)
	FLOAT _dX[3];							// mesh
	FLOAT _g				=9.81;			// gravitational constant
	FLOAT _nu	    		=0.000001787;	// kinmetic viscosity
	FLOAT _gamma_t			=0.0;			// wind constant
	FLOAT _gamma_b 			=0.0;			// friction constant
	FLOAT _u_a      		=0.0;			// wind speed in x direction (m/s)
	FLOAT _v_a      		=0.0;			// wind speed in y direction (m/s)
	FLOAT _precipitation 	=0.0;			// precipitation rate (m/s)
	FLOAT _dry_cell_error 	=0.001;			// error in modeling the dry cells
	FLOAT _tol_1d			=0.001;			// solver tolerance (1d)
	int _max_it_1d			=1000;			// maximum number of iterations for 1d solvers
	FLOAT _tol_2d			=0.001;			// solver tolerance (2d)
	int _max_it_2d			=1000;			// maximum number of iterations for 2d solvers
	int _output_flag 		=1;				// whether or not ro create output files
	FLOAT _out_flag_time_step=_dt;			// time step for printing output flag
	std::string _solver 	="PARALLEL";	// simulation type -> "PARALLEL" or "PETSC"
	int _block_size_2d;

protected:
	int _N[3] 				={20,20,10}	;	// Number of cells in xyz directions
	int _NGlobal[3];						// Number of cells in xyz directions
public:
	Parameters(int argc, char * argv[]);
	Parameters(int argc, char * argv[], Topology& topology);
	~Parameters();							// destructor
	void parse(int argc, char * argv[]); 	// method to parse inputs and set the parameters
	void print_parameters(); 				// print parameters to the consule

	//getters
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
	int GetBlockSize2d() const;		// just used for the petsc parallel 2d solver in case of well distributed domains
	int	  GetOutputFlag() const;
	FLOAT GetPrecipitation() const;
	FLOAT GetDryCellError() const;
	FLOAT get_tol_1d() const;
	FLOAT get_tol_2d() const;
	int get_max_it_1d() const;
	int get_max_it_2d() const;
	std::string get_solver_type() const;

	Topology& topology;
};
