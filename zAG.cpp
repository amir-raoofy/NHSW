#include "ParallelSimulation.h"
#include "Solver.h"

void ParallelSimulation::CalculateZAGI(){

	// (dz invA GI)	i+0.5
	// Domain + boundaries
	FLOAT s1=0;

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			solver_1d_Ai_->SetIndices(i,j);
			solver_1d_Ai_->SetBuffer(flowField_.g_i);
			solver_1d_Ai_->SetRhs(flowField_.g_i);
			solver_1d_Ai_->solve();
			
			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_i[map(i,j,k)]*x_[k];
			}
			flowField_.zag_i[map(i,j)]=s1;

		}
	}

}

void ParallelSimulation::CalculateZAGJ(){
	
	// (dz invA GJ)	j+0.5
	// Domain + boundaies

	FLOAT s1=0;

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			solver_1d_Aj_->SetIndices(i,j);
			solver_1d_Aj_->SetBuffer(flowField_.g_j);
			solver_1d_Aj_->SetRhs(flowField_.g_j);
			solver_1d_Aj_->solve();
			
			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_j[map(i,j,k)]*x_[k];
			}
			flowField_.zag_j[map(i,j)]=s1;

		}
	}

}
