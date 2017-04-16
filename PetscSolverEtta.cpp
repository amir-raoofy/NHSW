#include "PetscSimulation.h"
#include "Solver.h"

void PetscSimulation::UpdateEtta(){

	etta_solver_->set_time_step(time_step);
	etta_solver_->updateMat();
	etta_solver_->updateRHS();
	etta_solver_->solve();
	etta_solver_->updateField();

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.etta[map(i,j)] = -parameters_.GetHeight() + parameters_.GetDryCellError();
			}

		}
	}

	scenario_->updateBoundariesEtta();

}

