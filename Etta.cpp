#include "Simulation.h" 

void Simulation::InitEtta(){
  /*
   *	initialization for oscilation scenario
   */
	//	TODO how do we initialize boundary, do we do it specifically?
	// D + B
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.SetEtta()[i][j] = -0.1 + (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
		}
	}
	//test the initialization of initial water elevation
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetEtta()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
 }
