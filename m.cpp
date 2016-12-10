#include "Simulation.h"

// initialize m for specific scenario -> oscilation --> m = 0 everywhere
// D + B
void Simulation::Initm(){
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.Setm()[i][j] = floor( ( parameters_.GetHeight() - parameters_.GetHeight() )
										 									 / parameters_.get_dxdydz(2) );
		}
	}
	//test the initialization of initial water elevation
	std::cout << "print m" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.Getm()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
