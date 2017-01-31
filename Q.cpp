#include "Simulation.h"
#include "Solver.h"

void Simulation::InitQ(){
	//Domain + Boundary	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++){
				flowField_.SetQ()[i][j].push_back(0.0);
			}
		}
	}
	//@test the initializattion:
	std::cout << "test initialization of nonhydrostatic pressure: " << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetQ()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}

void Simulation::UpdateCellNumberQ(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetQ()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetQ()[i][j].push_back(0.0);
			}
			while (flowField_.GetQ()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetQ()[i][j].pop_back();
			}
		}
	}
}

void Simulation::SolveQ(){
	JacobiSolverQ q_solver(parameters_, flowField_);
	q_solver.SetParameters (0.00001,1000);
	q_solver.solve();

	//@test
	std::cout << "Solution of non-hydrostatic pressure:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetQ()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}
