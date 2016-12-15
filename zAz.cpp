#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitzAz(){	
	{
	// (dz invA dz)	i+0.5
	DiscreteLine buffer;
	JacobiSolverAI solver(parameters_, flowField_, buffer, flowField_.SetDzI()[0][0]);
	solver.SetParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
				
			buffer=flowField_.GetDzI()[i][j];
			solver.SetRhs(flowField_.SetDzI()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAZI()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzI()[i][j].begin(), 0.0);
		}
	}
	}// clear the stack
	//@test the initialization of Zt * inv A * ZI
	std::cout << "test initialization of  Zt * inv A * ZI" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetZAZI()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	// (dz invA dz)	j+0.5
	{
	DiscreteLine buffer;
	JacobiSolverAJ solver(parameters_, flowField_, buffer, flowField_.SetDzJ()[0][0]);
	solver.SetParameters (0.00001,1000);
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			buffer=flowField_.GetDzJ()[i][j];
			solver.SetRhs(flowField_.SetDzJ()[i][j]);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetZAZJ()[i][j]=std::inner_product(buffer.begin(), buffer.end(), flowField_.GetDzJ()[i][j].begin(), 0.0);
		}
	}
	}// clear the stack
	//@test the initialization of Zt * inv A * ZJ
	std::cout << "test initialization of  Zt * inv A * ZJ" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetZAZJ()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
