#include "Simulation.h"
#include "Solver.h"

void Simulation::CalculateZAGI(){
	// (dz invA dz)	i+0.5
	Petsc1DSolver solver(parameters_, flowField_);
	solver.setParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			solver.setIndices(i,j);
			solver.updateMat(flowField_.dz_i);
			solver.updateRHS(flowField_.g_i+map(i,j,0));
			solver.solve();
			solver.updateField(flowField_.zag_i, flowField_.dz_i);
		}
	}
}

void Simulation::CalculateZAGJ(){
	// (dz invA dz)	j+0.5
	Petsc1DSolver solver(parameters_, flowField_);
	solver.setParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			
			solver.setIndices(i,j);
			solver.updateMat(flowField_.dz_j);
			solver.updateRHS(flowField_.g_j+map(i,j,0));
			solver.solve();
			solver.updateField(flowField_.zag_j, flowField_.dz_j);
		}
	}
}
