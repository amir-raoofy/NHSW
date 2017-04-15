#include "Simulation.h"
#include "Solver.h"

void Simulation::UpdateV(){

	//calculation
	// Domain
	Petsc1DSolverV solver(parameters_, flowField_);
	solver.setParameters (0.00001,1000);
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

			solver.setIndices(i,j);
			solver.updateMat(flowField_.dz_j);
			solver.updateRHS();
			solver.solve();
			solver.updateField(flowField_.v);

			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.v[map(i,j,k)]=0.0;
			}

		}
	}

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.v[map(i,j,flowField_.m[map(i,j)])] = 0.0;
			}

		}
	}

	//Boundary
	scenario_->updateBoundariesV();

}
