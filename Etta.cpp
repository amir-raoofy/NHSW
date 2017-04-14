#include "Simulation.h" 
#include "Solver.h"
#include <math.h>

void Simulation::UpdateEtta(){
	JacobiSolverEtta etta_solver(parameters_, flowField_, *scenario_);
	etta_solver.SetParameters (0.00001,1000);
	etta_solver.set_time_step(time_step);
	etta_solver.solve();

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.etta[map(i,j)] = -parameters_.GetHeight() + parameters_.GetDryCellError();
			}

		}
	}

}
