#include "Simulation.h"

void Simulation::InitW(){
	//Domain + Boundary	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++){
				flowField_.SetW()[i][j].push_back(0.0);
			}
		}
	}

	//@test
	std::cout << "initialized velocity; W:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetV()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}

void Simulation::UpdateCellNumberW(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetW()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetW()[i][j].push_back(0.0);
			}
			while (flowField_.GetW()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetW()[i][j].pop_back();
			}
		}
	}
}

void Simulation::FirstStepUpdateW(){
	//TODO
}
