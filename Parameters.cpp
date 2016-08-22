#include <Parameters.h>

Parameters::Parameters():
	_T(1.0), _dt(0.1)
{
	_N[0]=10 ; _N[1]=10 ; _N[2]=10 ;
	_L[0]=1.0; _L[1]=1.0; _L[2]=1.0;
	std::cout << "Warning: The default values for parameters are used." << std::endl;
	_dX[0]=_L[0]/_N[0];
	_dX[1]=_L[1]/_N[1];
	_dX[2]=_L[2]/_N[2];
}

Parameters::Parameters(int argc, const char *argv[]):
	_T(1.0), _dt(0.1)
{
	_N[0]=10 ; _N[1]=10 ; _N[2]=10 ;
	_L[0]=1.0; _L[1]=1.0; _L[2]=1.0;
	this->parse(argc, argv);
	_dX[0]=_L[0]/_N[0];
	_dX[1]=_L[1]/_N[1];
	_dX[2]=_L[2]/_N[2];
}
Parameters::~Parameters(){}

void Parameters::parse(int argc, const char *argv[])  {

	if (argc!=9){
		std::cout << "Warning: The default values for parameters are used." << std::endl;
	}else{
		_N[0]  	= atoi(argv[1]);
		_N[1]  	= atoi(argv[2]);
		_N[2]  	= atoi(argv[3]);
		_T	 	= atof(argv[4]);
		_dt  	= atof(argv[5]);
		_L[0]	= atof(argv[6]);
		_L[1]	= atof(argv[7]);
		_L[2] 	= atof(argv[8]);
	}
}

float Parameters::get_sim_time(){
	return this->_T;
}
float Parameters::get_time_step(){
	return this->_dt;
}

int Parameters::get_num_cells(int dim){
	return _N[dim];
}
float Parameters::get_dxdydz(int dim){
	return _dX[dim];

}

void Parameters::print_parameters(){
	
	// print the header
	std::cout 	<< std::endl 
				<< "   ===================================="<< std::endl;
	std::cout 	<< "  |" << "\033[1;31mNon-hydrostatic Shallow Water solver\033[0m"
				<< "|" 	 <<  std::endl;
	std::cout 	<< "   ===================================="<< std::endl;
	
	//print the parameters
	std::cout 	<< "Number of cells in x-direction	-> 	"<< _N[0]	<<	std::endl
				<< "Number of cells in y-direction	-> 	"<< _N[1]	<<	std::endl
				<< "Number of cells in z-direction	-> 	"<< _N[2]	<<	std::endl
				<< "Simulation time 		-> 	"		<< _T		<<	std::endl
				<< "Time step			-> 	"			<< _dt		<<	std::endl
				<< "Length in x-direction		-> 	"	<< _L[0]	<<	std::endl
				<< "Length in y-direction		-> 	"	<< _L[1]	<<	std::endl
				<< "Length in z-direction		-> 	"	<< _L[2]	<<	std::endl;
}
