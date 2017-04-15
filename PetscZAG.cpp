#include "Simulation.h"
#include "Solver.h"

void Simulation::CalculateZAGI(){
	// (dz invA dz)	i+0.5

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
				
			petsc_solver_1d_Ai_->setIndices(i,j);
			petsc_solver_1d_Ai_->updateMat(flowField_.dz_i);
			petsc_solver_1d_Ai_->updateRHS(flowField_.g_i+map(i,j,0));
			petsc_solver_1d_Ai_->solve();
			petsc_solver_1d_Ai_->updateField(flowField_.zag_i, flowField_.dz_i);

		}
	}

}

void Simulation::CalculateZAGJ(){
	// (dz invA dz)	j+0.5

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			
			petsc_solver_1d_Aj_->setIndices(i,j);
			petsc_solver_1d_Aj_->updateMat(flowField_.dz_j);
			petsc_solver_1d_Aj_->updateRHS(flowField_.g_j+map(i,j,0));
			petsc_solver_1d_Aj_->solve();
			petsc_solver_1d_Aj_->updateField(flowField_.zag_j, flowField_.dz_j);

		}
	}

}
