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

	if (argc!=28){
		if (topology.id==0) {
			std::cout << "Warning: The default values for parameters are used." << std::endl;
		}
	}else{

		_N[0]  			= atoi(argv[1]);
		_N[1]  			= atoi(argv[2]);
		_N[2]  			= atoi(argv[3]);
		_T	 			= atof(argv[4]);
		_mat_ts			= atoi(argv[5]);
		_dt  			= atof(argv[6]);
		_tau 			= atof(argv[7]);
		_theta 			= atof(argv[8]);
		_L[0]			= atof(argv[9]);
		_L[1]			= atof(argv[10]);
		_L[2] 			= atof(argv[11]);
		_height 		= atof(argv[12]);
		_g	 			= atof(argv[13]);
		_nu				= atof(argv[14]);
		_gamma_t		= atof(argv[15]);
		_gamma_b		= atof(argv[16]);
		_u_a			= atof(argv[17]);
		_v_a			= atof(argv[18]);
		_precipitation 	= atof(argv[19]);
		_dry_cell_error = atof(argv[20]);
		_solver 		= 	   argv[21];
		_tol_1d 		= atof(argv[22]);
		_max_it_1d		= atoi(argv[23]);
		_tol_2d 		= atof(argv[24]);
		_max_it_2d 		= atoi(argv[25]);
		_output_flag	= atoi(argv[26]);
		_out_freq		= atoi(argv[27]);

	}
}

FLOAT Parameters::get_sim_time() const{
	return this->_T;
}

int Parameters::get_max_ts() const{
	return _mat_ts;
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

int Parameters::GetOutputFlag() const{
	return _output_flag;
}

int Parameters::GetOutFreq() const{
	return _out_freq;
}

void Parameters::print_parameters(){

	// print the header
	std::cout 	<< " ==============================================================="<< std::endl;
	std::cout 	<< "|" << "\033[1;31m                3D hydrostatic Surface Flow solver             \033[0m"
				<< "|" 	 <<  std::endl;
	std::cout 	<< " ==============================================================="<< std::endl;
	
	//print the parameters
	std::cout	<< "|Number of Processors 				-> "			<< std::setw(10) << topology.np		<< "   |" << std::endl
				<< "|Number of Processors in x direction		-> "	<< std::setw(10) << topology.npx	<< "   |" << std::endl
				<< "|Number of Processors in y direction		-> "	<< std::setw(10) << topology.npy	<< "   |" << std::endl
				<< "|Number of cells in x-direction			-> "		<< std::setw(10) << _NGlobal[0]		<< "   |" << std::endl
				<< "|Number of cells in y-direction			-> "		<< std::setw(10) << _NGlobal[1]		<< "   |" << std::endl
				<< "|Number of cells in z-direction			-> "		<< std::setw(10) << _NGlobal[2]		<< "   |" << std::endl
				<< "|Local Number of cells (x) in each processor	-> "<< std::setw(10) << _N[0]			<< "   |" << std::endl
				<< "|Local Number of cells (y) in each processor	-> "<< std::setw(10) << _N[1]			<< "   |" << std::endl
				<< "|Local Number of cells (z) in each processor	-> "<< std::setw(10) << _N[2]			<< "   |" << std::endl
				<< "|Simulation time 				-> "				<< std::setw(10) << _T				<< "   |" << std::endl
				<< "|Max number of time steps			-> "			<< std::setw(10) << _mat_ts			<< "   |" << std::endl
				<< "|Time step					-> "					<< std::setw(10) << _dt				<< "   |" << std::endl
				<< "|Stability safety factor			-> "			<< std::setw(10) << _tau			<< "   |" << std::endl
				<< "|Theta in numerical scheme			-> "			<< std::setw(10) << _theta			<< "   |" << std::endl
				<< "|Length in x-direction				-> "			<< std::setw(10) << _L[0]			<< "   |" << std::endl
				<< "|Length in y-direction				-> "			<< std::setw(10) << _L[1]			<< "   |" << std::endl
				<< "|Length in z-direction				-> "			<< std::setw(10) << _L[2]			<< "   |" << std::endl
				<< "|Free surface water height			-> "			<< std::setw(10) << _height			<< "   |" << std::endl
				<< "|Gravitational constant				-> "			<< std::setw(10) << _g				<< "   |" << std::endl
				<< "|Kinematic viscosity				-> "			<< std::setw(10) << _nu				<< "   |" << std::endl
				<< "|Wind constant					-> "				<< std::setw(10) << _gamma_t		<< "   |" << std::endl
				<< "|Friction constant				-> "				<< std::setw(10) << _gamma_b		<< "   |" << std::endl
				<< "|Horizontal speed of wind			-> "			<< std::setw(10) << _u_a			<< "   |" << std::endl
				<< "|Vertical speed of wind				-> "			<< std::setw(10) << _v_a			<< "   |" << std::endl
				<< "|Precipitation rate				-> "				<< std::setw(10) << _precipitation	<< "   |" << std::endl
				<< "|Error in modeling dry cells			-> "		<< std::setw(10) << _dry_cell_error	<< "   |" << std::endl
				<< "|Solver type					-> "				<< std::setw(10) << _solver 		<< "   |" << std::endl
				<< "|Maximum tolerance for 1d solvers		-> "		<< std::setw(10) << _tol_1d 		<< "   |" << std::endl
				<< "|Maximum iteration number for 1d solvers	-> "	<< std::setw(10) << _max_it_1d 		<< "   |" << std::endl
				<< "|Maximum tolerance for 2d solvers		-> "		<< std::setw(10) << _tol_2d 		<< "   |" << std::endl
				<< "|Maximum iteration number for 2d solvers	-> "	<< std::setw(10) << _max_it_2d 		<< "   |" << std::endl
				<< "|VTK Output flag				-> "				<< std::setw(10) << _output_flag	<< "   |" << std::endl
				<< "|VTK Output time step				-> "			<< std::setw(10) << _out_freq		<< "   |" << std::endl
				<< "\033[1;31m =============================================================== \033[0m"   	<< std::endl;

}
