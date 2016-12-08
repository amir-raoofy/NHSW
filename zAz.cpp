#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitzAz(){	
	{
	// (dz invA dz)	i+0.5
	DiscreteLine buffer;
	JacobiSolverAI solver(parameters_, flowField_, buffer);
	solver.SetParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	
			buffer=flowField_.GetDzI()[i][j];
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZazI()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzI()[i][j].begin(), 0.0);
		}
	}
	}// clear the stack
	
	// (dz invA dz)	j+0.5
	{
	DiscreteLine buffer;
	JacobiSolverAJ solver(parameters_, flowField_, buffer);
	solver.SetParameters (0.00001,1000);
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	
			buffer=flowField_.GetDzJ()[i][j];
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZazJ()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzJ()[i][j].begin(), 0.0);
		}
	}
	}// clear the stack
}
