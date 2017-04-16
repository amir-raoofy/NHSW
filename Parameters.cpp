#include "Parameters.h"

Parameters::Parameters(int argc, char *argv[]):
	topology(*(new Topology()))
{

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

Parameters::Parameters(int argc, char *argv[], Topology& topology):
	topology(topology)
{
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

	if (argc!=27){
		std::cout << "Warning: The default values for parameters are used." << std::endl;
	}else{
		_N[0]  	= atoi(argv[1]);
		_N[1]  	= atoi(argv[2]);
		_N[2]  	= atoi(argv[3]);
		_T	 		= atof(argv[4]);
		_dt  		= atof(argv[5]);
		_tau 	= atof(argv[6]);
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
		_precipitation = atof(argv[18]);
		_dry_cell_error =	atof(argv[19]);
		_tol_1d = atof(argv[20]);
		_max_it_1d = atoi(argv[21]);
		_tol_2d = atof(argv[22]);
		_max_it_2d = atoi(argv[23]);
		_output_flag= atoi(argv[24]);
		_out_flag_time_step= atoi(argv[25]);
		_solver = argv[26];

	}
}

FLOAT Parameters::get_sim_time() const{
	return this->_T;
}

FLOAT Parameters::GetCubeLength(int dim) const{
	return this->_L[dim];
}

FLOAT Parameters::get_time_step() const{
	return this->_dt;
}

int Parameters::get_num_cells(int dim) const{
	return _N[dim];
}

FLOAT Parameters::get_dxdydz(int dim) const{
	return _dX[dim];
}
FLOAT Parameters::get_vis() const{
	return _nu;
}

FLOAT Parameters::get_gamma_b() const{
	return _gamma_b;
}

FLOAT Parameters::get_gamma_t() const{
	return _gamma_t;
}

FLOAT Parameters::get_viscosity() const{
	return _nu;
}

FLOAT Parameters::get_theta() const{
	return _theta;
}


FLOAT Parameters::get_g() const{
	return _g;
}

FLOAT Parameters::get_u_a() const{
	return _u_a;
}
FLOAT Parameters::get_v_a() const{
	return _v_a;
}

FLOAT Parameters::GetHeight() const{
	return _height;
}

int Parameters::GetBlockSize2d() const{
	return _block_size_2d;
}

int Parameters::GetOutputFlag() const{
	return _output_flag;
}

FLOAT Parameters::GetPrecipitation() const{
	return _precipitation;
}
	
FLOAT Parameters::get_tau() const{
	return _tau;
}

FLOAT Parameters::GetDryCellError() const{
	return _dry_cell_error;
}

FLOAT Parameters::get_tol_1d() const{
	return _tol_1d;
}

FLOAT Parameters::get_tol_2d() const{
	return _tol_2d;
}

int Parameters::get_max_it_1d() const{
	return _max_it_1d;
}

int Parameters::get_max_it_2d() const{
	return _max_it_2d;
}

std::string Parameters::get_solver_type() const{
	return _solver;
}

void Parameters::print_parameters(){

	// print the header
	std::cout 	<< " ========================================================"<< std::endl;
	std::cout 	<< "|" << "\033[1;31m            3D hydrostatic Surface Flow solver         \033[0m"
				<< "|" 	 <<  std::endl;
	std::cout 	<< "|========================================================"<< std::endl;
	
	//print the parameters
	std::cout	<< "|Number of Processors 				-> "			<< topology.np	<<	std::endl
				<< "|Number of Processors in x direction		-> "	<< topology.npx	<<	std::endl
				<< "|Number of Processors in y direction		-> "	<< topology.npy	<<	std::endl
				<< "|Number of cells in x-direction			-> "		<< _NGlobal[0]	<<	std::endl
				<< "|Number of cells in y-direction			-> "		<< _NGlobal[1]	<<	std::endl
				<< "|Number of cells in z-direction			-> "		<< _NGlobal[2]	<<	std::endl
				<< "|Local Number of cells (x) in each processor	-> "<< _N[0]		<<	std::endl
				<< "|Local Number of cells (y) in each processor	-> "<< _N[1]		<<	std::endl
				<< "|Local Number of cells (z) in each processor	-> "<< _N[2]		<<	std::endl
				<< "|Simulation time 				-> "				<< _T			<<	std::endl
				<< "|Time step					-> "					<< _dt			<<	std::endl
				<< "|stability safety factor			-> "			<< _tau			<<	std::endl
				<< "|theta in numerical scheme			-> "			<< _theta		<<	std::endl
				<< "|Length in x-direction				-> "			<< _L[0]		<<	std::endl
				<< "|Length in y-direction				-> "			<< _L[1]		<<	std::endl
				<< "|Length in z-direction				-> "			<< _L[2]		<<	std::endl
				<< "|free surface water height			-> "			<< _height		<<	std::endl
				<< "|gravitational constant				-> "			<< _g			<<	std::endl
				<< "|kinematic viscosity				-> "			<< _nu			<<	std::endl
				<< "|Wind constant					-> "				<< _gamma_t		<<	std::endl
				<< "|friction constant				-> "				<< _gamma_b		<<	std::endl
				<< "|horizontal speed of wind			-> "			<< _u_a			<<	std::endl
				<< "|vertical speed of wind				-> "			<< _v_a			<<	std::endl
				<< "|precipitation rate				-> "				<< _precipitation<< std::endl
				<< "|solver type					-> "				<< _solver 		<<  std::endl
				<< "|maximum tolerance for 1d solvers		-> "		<< _tol_1d 		<<  std::endl
				<< "|maximum iteration number for 1d solvers	-> "	<< _max_it_1d 	<<  std::endl
				<< "|maximum tolerance for 2d solvers		-> "		<< _tol_2d 		<<  std::endl
				<< "|maximum iteration number for 2d solvers	-> "	<< _max_it_2d 	<<  std::endl
				<< "|Output flag					-> "				<< _output_flag	<<	std::endl
				<< "|Output flag					-> "				<< _out_flag_time_step	<<	std::endl
				<< "\033[1;31m|=========================================================\033[0m"  << std::endl;

}
