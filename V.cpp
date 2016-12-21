#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitV(){
	// Domain + Boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++){
				flowField_.SetV()[i][j].push_back(0.0);
			}
		}
	}

	//@test
	std::cout << "initialized velocity; V:" << std::endl;
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

void Simulation::UpdateCellNumberV(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetV()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetV()[i][j].push_back(parameters_.get_v_a());
			}
			while (flowField_.GetV()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetV()[i][j].pop_back();
			}
		}
	}
}

void Simulation::FirstStepUpdateV(){
	//calculation
	DiscreteLine rhs;
	DiscreteLine buffer;
	JacobiSolverAJ solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
/*			for(int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++){
					flowField_.SetV()[i][j][k]=10.0;
				}
				*/
			rhs.clear();
			std::transform(		flowField_.GetDzJ()[i][j].begin(),flowField_.GetDzJ()[i][j].end(), std::back_inserter(rhs), std::bind1st(std::multiplies<FLOAT>(),
			(flowField_.GetEtta()[i][j+1]-flowField_.GetEtta()[i][j]) * parameters_.get_theta() * parameters_.get_g() * parameters_.get_time_step() / parameters_.get_dxdydz(1)		));
			std::transform(flowField_.GetGJ()[i][j].begin(), flowField_.GetGJ()[i][j].end(), rhs.begin(), rhs.begin(), std::minus<FLOAT>());
			buffer = flowField_.SetV()[i][j];
			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetV()[i][j] = buffer;
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]+1; k++) {
			flowField_.SetV()[0][j][k]=flowField_.GetV()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]+1; k++) {
			flowField_.SetV()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetV()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]+1; k++) {
			flowField_.SetV()[i][0][k]=flowField_.GetV()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]+1; k++) {
			flowField_.SetV()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetV()[i][parameters_.get_num_cells(0)][k];
		}
	}	//@test
	std::cout << "first step velocity update; V:" << std::endl;
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
