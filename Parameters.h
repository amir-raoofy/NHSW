#include <iostream>
#include <cstdlib>

class Parameters
{
private:
	float _T	;				// Time span of the simulation
	float _dt	;				// Time-step of the numerical scheme
	float _L[3]	;				// Geometery of the simulation cube
	float _dX[3];

protected:
	int _N[3]	;				// Number of cells in xyz directions

public:
	Parameters();						// constructor
	Parameters(int argc, const char * argv[]);
	~Parameters();						// destructor
	void parse(int argc, const char * argv[]); 	// method to parse inputs and set the parameters
	void print_parameters(); 			// print parameters to the consule

	float get_sim_time();
	float get_time_step();
	int get_num_cells(int dim);
	float get_dxdydz(int dim);
};
