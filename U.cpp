#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

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
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
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

void Simulation::UpdateCellNumberU(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetU()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetU()[i][j].push_back(0.0);
			}
			while (flowField_.GetU()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetU()[i][j].pop_back();
			}
		}
	}
}

void Simulation::FirstStepUpdateU(){
	//calculation
	DiscreteLine rhs;
	DiscreteLine buffer;
	JacobiSolverAI solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
/*			for(int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++){
					flowField_.SetU()[i][j][k]=10.0;
				}
				*/
			rhs.clear();
			std::transform(		flowField_.GetDzI()[i][j].begin(),flowField_.GetDzI()[i][j].end(), std::back_inserter(rhs), std::bind1st(std::multiplies<FLOAT>(),
			(flowField_.GetEtta()[i+1][j]-flowField_.GetEtta()[i][j]) * parameters_.get_theta() * parameters_.get_g() * parameters_.get_time_step() / parameters_.get_dxdydz(0)		));
			std::transform(flowField_.GetGI()[i][j].begin(), flowField_.GetGI()[i][j].end(), rhs.begin(), rhs.begin(), std::minus<FLOAT>());
			buffer = flowField_.SetU()[i][j];
			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetU()[i][j] = buffer;
		}
	}
	//@test
	std::cout << "first step velocity update; U:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
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
