#include <iostream>
#include <cstdlib>

class Parameters
{
private:
	float _T;							// Time span of the simulation
	float _dt;							// Time-step of the numerical scheme
	float _Lx, _Ly, _Lz;				// Geometery of the simulation cube

protected:
	int _Nx, _Ny, _Nz;					// Number of cells in xyz directions

public:
	Parameters();						// constructor
	~Parameters();						// destructor
	void parse(int argc, const char * argv[]); 	// method to parse inputs and set the parameters
	void print_parameters(); 			// print parameters to the consule
};
