#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::CalculateZAGI(){
	// (dz invA GI)	i+0.5
	// Domain + boundaries
	DiscreteLine buffer;
	JacobiSolverAI solver(parameters_, flowField_, buffer, flowField_.SetGI()[0][0]);
	solver.SetParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			buffer=flowField_.GetDzI()[i][j];
			solver.SetRhs(flowField_.SetGI()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAGI()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzI()[i][j].begin(), 0.0);
		}
	}
	//TODO decide on the boundary; since GI is not initialized and directly calcualated, the boundaries at least once should be set to at least zero to be on the safe side
}

void Simulation::CalculateZAGJ(){
	// (dz invA GJ)	j+0.5
	// Domain + boundaies
	DiscreteLine buffer;
	JacobiSolverAJ solver(parameters_, flowField_, buffer, flowField_.SetGJ()[0][0]);
	solver.SetParameters (0.00001,1000);
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			buffer=flowField_.GetDzJ()[i][j];
			solver.SetRhs(flowField_.SetGJ()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAGJ()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzJ()[i][j].begin(), 0.0);
		}
	}
	//TODO decide on the boundary; since GJ is not initialized and directly calcualated, the boundaries at least once should be set to at least zero to be on the safe side
}
