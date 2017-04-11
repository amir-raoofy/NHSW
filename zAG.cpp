#include "Simulation.h"
#include "Solver.h"
#include <algorithm>
#include <numeric>

void Simulation::CalculateZAGI(){

	// (dz invA GI)	i+0.5
	// Domain + boundaries
	FLOAT s1=0;
	FLOAT* rhs= new FLOAT [parameters_.get_num_cells(2)];
	FLOAT* buffer= new FLOAT [parameters_.get_num_cells(2)];
	JacobiSolverAI solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);

	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
	
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				rhs[k] = flowField_.g_i[map(i,j,k)];
			}

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				buffer[k] = flowField_.dz_i[map(i,j,k)];
			}
			
			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();
			
			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_i[map(i,j,k)]*buffer[k];
			}
			flowField_.zag_i[map(i,j)]=s1;

		}
	}

}

void Simulation::CalculateZAGJ(){
	
	// (dz invA GJ)	j+0.5
	// Domain + boundaies
	FLOAT s1=0;
	FLOAT* rhs= new FLOAT [parameters_.get_num_cells(2)];
	FLOAT* buffer= new FLOAT [parameters_.get_num_cells(2)];
	JacobiSolverAJ solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);
	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				rhs[k] = flowField_.dz_j[map(i,j,k)];
			}

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				buffer[k] = flowField_.dz_j[map(i,j,k)];
			}

			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			s1=0;
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_j[map(i,j,k)]*buffer[k];
			}
			flowField_.zag_j[map(i,j)]=s1;
	
		}
	}
	
}
