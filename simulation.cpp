#include <simulation.h>

Simulation::Simulation(flowField *flowfield, Parameters *parameters){

	this->_parameters = parameters;
	this->_flowfield  = flowfield;
}

Simulation::~Simulation(){}

void Simulation::run(){
	
	Output output(*_parameters, *_flowfield);
		
	_flowfield -> init_data();
	_flowfield -> init_vel_field();
	_flowfield -> init_dz();
	_flowfield -> init_h();
	_flowfield -> init_m();
//	_flowfield -> print_data();
	output.write(*_flowfield, 0, "./output/");
	for (int i = 1; i < 2; i++) {
	_flowfield -> update_M();
	_flowfield -> update_A();
	_flowfield -> update_F();
	_flowfield -> update_G();
//	_flowfield -> test_solver();
	_flowfield -> update_S();
	_flowfield -> update_T();
	_flowfield -> update_h();
	_flowfield -> update_u_v();
	_flowfield -> solve_q();
	_flowfield -> update_u_v_w();
	_flowfield -> solve_h();

	output.write(*_flowfield, i, "./output/");
	}
	_flowfield -> print_data();
}
