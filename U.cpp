#include "Simulation.h"

void Simulation::InitU(){
	// Domain + Boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++){
				flowField_.SetU()[i][j].push_back(0.0);
			}
		}
	}

	//@test
	std::cout << "initialized velocity; U:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetU()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}
