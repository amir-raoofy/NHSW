#include "Simulation.h"

// initialize m for specific scenario -> oscilation --> m = 0 everywhere
void Simulation::Initm(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			flowField_.Setm()[i][j] = floor( ( parameters_.GetHeight() - parameters_.GetHeight() )
										 									 / parameters_.get_dxdydz(2) );
		}
	}
	//test the initialization of initial water elevation
	/*
	 *for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	 *  for (int i = 0; i < parameters_.get_num_cells(0); i++) {
	 *    std::cout << flowField_.Getm()[i][j] << "\t";
	 *  }
	 *  std::cout << std::endl;
	 *}
	 */
}
