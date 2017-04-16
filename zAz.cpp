#include "ParallelSimulation.h"
#include "Solver.h"

void ParallelSimulation::CalculateZAZI(){

	// (dz invA dz)	i+0.5
	FLOAT s1=0;

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			solver_1d_Ai_->SetIndices(i,j);
			solver_1d_Ai_->SetBuffer(flowField_.dz_i);
			solver_1d_Ai_->SetRhs(flowField_.dz_i);
			solver_1d_Ai_->solve();
			
			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_i[map(i,j,k)]*x_[k];
			}
			flowField_.zaz_i[map(i,j)]=s1;

		}
	}

}
void ParallelSimulation::CalculateZAZJ(){
		
	// (dz invA dz)	j+0.5
	FLOAT s1=0;
	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			solver_1d_Aj_->SetIndices(i,j);
			solver_1d_Aj_->SetBuffer(flowField_.dz_j);
			solver_1d_Aj_->SetRhs(flowField_.dz_j);
			solver_1d_Aj_->solve();

			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_j[map(i,j,k)]*x_[k];
			}
			flowField_.zaz_j[map(i,j)]=s1;
	
		}
	}

}
