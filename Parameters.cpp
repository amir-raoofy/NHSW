#include <Parameters.h>

Parameters::Parameters():
	_Nx(0), _Ny(0), _Nz(0),
	_T(0.0), _dt(0.0), _Lx(0.0), _Ly(0.0), _Lz(0.0)
{}

Parameters::~Parameters(){}

void Parameters::parse(int argc, const char *argv[])  {
	_Nx  = atoi(argv[1]);
	_Ny  = atoi(argv[2]);
	_Nz  = atoi(argv[3]);
	_T	 = atof(argv[4]);
	_dt  = atof(argv[5]);
	_Lx  = atof(argv[6]);
	_Ly  = atof(argv[7]);
	_Lz  = atof(argv[8]);
}

void Parameters::print_parameters(){
	
	// print the header
	std::cout 	<< std::endl 
				<< "   ===================================="<< std::endl;
	std::cout 	<< "  |" << "\033[1;31mNon-hydrostatic Shallow Water solver\033[0m"<< "|" <<  std::endl;
	std::cout 	<< "   ===================================="<< std::endl;
	
	//print the parameters
	std::cout 	<< "Number of cells in x-direction	-> 	"<< _Nx	<<	std::endl
				<< "Number of cells in y-direction	-> 	"<< _Ny	<<	std::endl
				<< "Number of cells in z-direction	-> 	"<< _Nz	<<	std::endl
				<< "Simulation time 		-> 	"		<< _T	<<	std::endl
				<< "Time step			-> 	"			<< _dt	<<	std::endl
				<< "Length in x-direction		-> 	"	<< _Lx	<<	std::endl
				<< "Length in y-direction		-> 	"	<< _Ly	<<	std::endl
				<< "Length in z-direction		-> 	"	<< _Lz	<<	std::endl;
}
