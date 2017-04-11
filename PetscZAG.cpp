#include "Simulation.h"
#include "Solver.h"

void Simulation::CalculateZAGI(){
	// (dz invA dz)	i+0.5
	Petsc1DSolver solver(parameters_, flowField_,flowField_.dz_i, flowField_.g_i, flowField_.zag_i);
	solver.setParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			solver.setIndices(i,j);
			solver.updateMat();
			solver.updateRHS();
			solver.solve();
			solver.updateField();
		}
	}
}

void Simulation::CalculateZAGJ(){
	// (dz invA dz)	j+0.5
	Petsc1DSolver solver(parameters_, flowField_,flowField_.dz_j, flowField_.g_j, flowField_.zag_j);
	solver.setParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			
			solver.setIndices(i,j);
			solver.updateMat();
			solver.updateRHS();
			solver.solve();
			solver.updateField();
		}
	}
}
