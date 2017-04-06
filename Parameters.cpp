#include "Parameters.h"

Parameters::Parameters():
	_T(1.0), _dt(0.1),topology(*(new Topology()))

{
	_N[0]=10 ; _N[1]=10 ; _N[2]=10 ;
	_L[0]=1.0; _L[1]=1.0; _L[2]=1.0;
	std::cout << "Warning: The default values for parameters are used." << std::endl;
	_dX[0]=_L[0]/_N[0];
	_dX[1]=_L[1]/_N[1];
	_dX[2]=_L[2]/_N[2];
	_output_flag=1;
	_NGlobal[0]=_N[0];
	_NGlobal[1]=_N[1];
	_NGlobal[2]=_N[2];
	_N[0]/=topology.npx;
	_N[1]/=topology.npy;
	_block_size_2d = _N[0]*_N[1]; 

	print_parameters();
	
}

Parameters::Parameters(int argc, char *argv[]):
	_T(1.0), _dt(0.1),topology(*(new Topology()))
{
	_N[0]=10 ; _N[1]=10 ; _N[2]=10 ;
	_L[0]=1.0; _L[1]=1.0; _L[2]=1.0;
	this->parse(argc, argv);
	_output_flag=1;
	_dX[0]=_L[0]/_N[0];
	_dX[1]=_L[1]/_N[1];
	_dX[2]=_L[2]/_N[2];
	_NGlobal[0]=_N[0];
	_NGlobal[1]=_N[1];
	_NGlobal[2]=_N[2];
	_block_size_2d = _N[0]*_N[1]; 
	
	print_parameters();	
}

Parameters::Parameters(int argc, char *argv[], Topology& topology):
	_T(1.0), _dt(0.1), topology(topology)
{
	_N[0]=10 ; _N[1]=10 ; _N[2]=10 ;
	_L[0]=1.0; _L[1]=1.0; _L[2]=1.0;
	this->parse(argc, argv);
	_dX[0]=_L[0]/_N[0];
	_dX[1]=_L[1]/_N[1];
	_dX[2]=_L[2]/_N[2];
	_NGlobal[0]=_N[0];
	_NGlobal[1]=_N[1];
	_NGlobal[2]=_N[2];
	_N[0]/=topology.npx;
	_N[1]/=topology.npy;
	_block_size_2d = _N[0]*_N[1]; 

	if (topology.id==0) {
		print_parameters();	
	}
}

Parameters::~Parameters(){}

void Parameters::parse(int argc, char *argv[])  {

	if (argc!=18){
		std::cout << "Warning: The default values for parameters are used." << std::endl;
	}else{
		_N[0]  	= atoi(argv[1]);
		_N[1]  	= atoi(argv[2]);
		_N[2]  	= atoi(argv[3]);
		_T	 		= atof(argv[4]);
		_dt  		= atof(argv[5]);
		_output_flag= atof(argv[6]);
		_theta 	= atof(argv[7]);
		_L[0]		= atof(argv[8]);
		_L[1]		= atof(argv[9]);
		_L[2] 	= atof(argv[10]);
		_height =	atof(argv[11]);
		_g	 		= atof(argv[12]);
		_nu			= atof(argv[13]);
		_gamma_t= atof(argv[14]);
		_gamma_b= atof(argv[15]);
		_u_a		= atof(argv[16]);
		_v_a		= atof(argv[17]);
	}
}

float Parameters::get_sim_time() const{
	return this->_T;
}

float Parameters::GetCubeLength(int dim) const{
	return this->_L[dim];
}

float Parameters::get_time_step() const{
	return this->_dt;
}

int Parameters::get_num_cells(int dim) const{
	return _N[dim];
}

float Parameters::get_dxdydz(int dim) const{
	return _dX[dim];
}
float Parameters::get_vis() const{
	return _nu;
}

float Parameters::get_gamma_b() const{
	return _gamma_b;
}

float Parameters::get_gamma_t() const{
	return _gamma_t;
}

float Parameters::get_viscosity() const{
	return _nu;
}

float Parameters::get_theta() const{
	return _theta;
}


float Parameters::get_g() const{
	return _g;
}

float Parameters::get_u_a() const{
	return _u_a;
}
float Parameters::get_v_a() const{
	return _v_a;
}

float Parameters::GetHeight() const{
	return _height;
}

float Parameters::GetBlockSize2d() const{
	return _block_size_2d;
}

float Parameters::GetOutputFlag() const{
	return _output_flag;
}

void Parameters::print_parameters(){
	
	// print the header
	std::cout 	<< std::endl 
				<< "   ===================================="<< std::endl;
	std::cout 	<< "  |" << "\033[1;31mNon-hydrostatic Shallow Water solver\033[0m"
				<< "|" 	 <<  std::endl;
	std::cout 	<< "   ===================================="<< std::endl;
	
	//print the parameters
	std::cout 	<< "Number of cells in x-direction	-> 	"<< _NGlobal[0]	<<	std::endl
				<< "Number of cells in y-direction	-> 	"<< _NGlobal[1]	<<	std::endl
				<< "Number of cells in z-direction	-> 	"<< _NGlobal[2]	<<	std::endl
				<< "Simulation time 		-> 	"		<< _T		<<	std::endl
				<< "Time step			-> 	"			<< _dt		<<	std::endl
				<< "Output flag			-> 	"			<< _output_flag	<<	std::endl
				<< "theta in numerical scheme	-> 	"	<< _theta	<<	std::endl
				<< "Length in x-direction		-> 	"	<< _L[0]	<<	std::endl
				<< "Length in y-direction		-> 	"	<< _L[1]	<<	std::endl
				<< "Length in z-direction		-> 	"	<< _L[2]	<<	std::endl
				<< "gravitational constant		-> 	"	<< _g		<<	std::endl
				<< "kinematic viscosity		-> 	"	<< _nu		<<	std::endl
				<< "Wind constant			-> 	"	<< _gamma_t	<<	std::endl
				<< "friction constant		-> 	"	<< _gamma_b	<<	std::endl
				<< "horizontal speed of wind	-> 	"	<< _u_a		<<	std::endl
				<< "vertical speed of wind		-> 	"	<< _v_a		<<	std::endl
				<< "\033[1;31m==========================================\033[0m"  << std::endl;
}
