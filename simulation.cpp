#include <simulation.h>

Simulation::Simulation(flowField *flowfield, Parameters *parameters){

	this->_parameters = parameters;
	this->_flowfield  = flowfield;
}

Simulation::~Simulation(){}

void Simulation::run(){
	_flowfield -> init_data();
	_flowfield -> init_vel_field();
	_flowfield -> init_dz();
	_flowfield -> init_h();
	_flowfield -> init_m();
	_flowfield -> print_data();
	for (int i = 0; i < 100; i++) {
	_flowfield -> update_M();
	_flowfield -> update_A();
	_flowfield -> update_F();
	_flowfield -> update_G();
//	_flowfield -> test_solver();
	_flowfield -> update_S();
	_flowfield -> update_T();
	_flowfield -> update_h();
    _flowfield -> update_u_v();
	}
	_flowfield -> print_data();
}
