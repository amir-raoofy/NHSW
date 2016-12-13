#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitzAGI(){
	// (dz invA GI)	i+0.5
	// Domain
	DiscreteLine buffer;
	JacobiSolverAI solver(parameters_, flowField_, buffer, flowField_.SetGI()[0][0]);
	solver.SetParameters (0.00001,1000);

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
	
			buffer=flowField_.GetDzI()[i][j];
			solver.SetRhs(flowField_.SetGI()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAGI()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzI()[i][j].begin(), 0.0);
		}
	}
	//@test the initialization of Zt * inv A * GI
	std::cout << "test initialization of  Zt * inv A * GI" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetZAGI()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void Simulation::InitzAGJ(){
	// (dz invA GJ)	j+0.5
	// Domain
	DiscreteLine buffer;
	JacobiSolverAJ solver(parameters_, flowField_, buffer, flowField_.SetGJ()[0][0]);
	solver.SetParameters (0.00001,1000);
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
	
			buffer=flowField_.GetDzJ()[i][j];
			solver.SetRhs(flowField_.SetGJ()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAGJ()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzJ()[i][j].begin(), 0.0);
		}
	}
	//@test the initialization of Zt * inv A * GJ
	std::cout << "test initialization of  Zt * inv A * GJ" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetZAGJ()[i][j] << "\t";
		}
		std::cout << std::endl;
	}

}
