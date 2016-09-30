#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
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
protected:
	int _N[3]	;				// Number of cells in xyz directions
public:
	Parameters();						// constructor
	Parameters(int argc, const char * argv[]);
	~Parameters();						// destructor
	void parse(int argc, const char * argv[]); 	// method to parse inputs and set the parameters
	void print_parameters(); 			// print parameters to the consule

	const float get_sim_time();
	const float get_time_step();
	const int   get_num_cells(int dim);
	const float get_dxdydz(int dim);
	const float get_vis();
	const float get_gamma_b();
	const float get_gamma_t();
	const float get_viscosity();
	const float get_theta();
	const float get_g();
	const float get_u_a();
	const float get_v_a();
};
