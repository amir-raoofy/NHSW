#include "ParallelSimulation.h"
#include "Solver.h"

void ParallelSimulation::UpdateEtta(){
	etta_solver_->set_time_step(time_step);
	etta_solver_->solve();

	FLOAT t1=0.0,t2=0.0,t3=0.0,t4=0.0;

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+1; j++) {

			t1 = parameters_.GetHeight()+flowField_.etta[map(i  ,j)];
			t2 = parameters_.GetHeight()+flowField_.etta[map(i+1,j)];
			t3 = parameters_.GetHeight()+flowField_.etta[map(i,  j)];
			t4 = parameters_.GetHeight()+flowField_.etta[map(i,j+1)];

			if (t1<=0.0 && t2 <=0.0) {
				flowField_.etta[map(i,j)]=0.0;
				flowField_.etta[map(i+1,j)]=0.0;
			}

			if (t1>=0.0 && t2 <=0.0) {
				flowField_.etta[map(i+1,j)]=flowField_.etta[map(i,j)];
			}

			if (t1<=0.0 && t2 >=0.0) {
				flowField_.etta[map(i,j)]=flowField_.etta[map(i+1,j)];
			}

			if (t3<=0.0 && t4 <=0.0) {
				flowField_.etta[map(i,j)]=0.0;
				flowField_.etta[map(i,j+1)]=0.0;
			}

			if (t3>=0.0 && t4 <=0.0) {
				flowField_.etta[map(i,j+1)]=flowField_.etta[map(i,j)];
			}

			if (t3<=0.0 && t4 >=0.0) {
				flowField_.etta[map(i,j)]=flowField_.etta[map(i,j+1)];
			}

			/*
			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.etta[map(i,j)] = -parameters_.GetHeight() + parameters_.GetDryCellError();
			}
			*/

		}
	}

	scenario_->updateBoundariesEtta();

}
