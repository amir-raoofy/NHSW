#include "ParallelSimulation.h"
#include "Solver.h"

void ParallelSimulation::UpdateU(){

	//calculation
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

			solver_1d_Ai_->SetIndices(i,j);
			solver_1d_Ai_->SetBuffer(flowField_.u);

			//instead of set rhs
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				rhs_[k] = flowField_.g_i[map(i,j,k)] - flowField_.dz_i[map(i,j,k)]
						*(flowField_.etta[map(i+1,j)]-flowField_.etta[map(i,j)]) 
						*parameters_.get_theta() * parameters_.get_g() 
						* time_step / parameters_.get_dxdydz(0);
			}

			solver_1d_Ai_->solve();

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				flowField_.u[map(i,j,k)] = x_[k] ;
			}

			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.u[map(i,j,k)]=0.0;
			}

		}
	}

	/*
	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.u[map(i,j,flowField_.m[map(i,j)])] = 0.0;
			}

		}
	}


	*/
	scenario_->updateBoundariesU();
}
