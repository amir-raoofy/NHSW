#include "Simulation.h"
#include "Solver.h"

void Simulation::UpdateU(){

	//calculation
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

			petsc_solver_1d_u_Ai_->setIndices(i,j);
			petsc_solver_1d_u_Ai_->updateMat(flowField_.dz_i);
			petsc_solver_1d_u_Ai_->updateRHS();
			petsc_solver_1d_u_Ai_->solve();
			petsc_solver_1d_u_Ai_->updateField(flowField_.u);

			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.u[map(i,j,k)]=0.0;
			}

		}
	}

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.u[map(i,j,flowField_.m[map(i,j)])] = 0.0;
			}

		}
	}

	scenario_->updateBoundariesU();

}
