#include "Simulation.h"
#include "Solver.h"

void Simulation::InitV(){
	// Domain + Boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.v[map(i,j,k)]=0.0;
			}
		}
	}
}

void Simulation::UpdateV(){
	//calculation
	FLOAT* rhs= new FLOAT [parameters_.get_num_cells(2)];
	FLOAT* buffer= new FLOAT [parameters_.get_num_cells(2)];
	JacobiSolverAJ solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				rhs[k] = flowField_.g_j[map(i,j,k)] - flowField_.dz_j[map(i,j,k)]
						*(flowField_.etta[map(i,j+1)]-flowField_.etta[map(i,j)]) 
						*parameters_.get_theta() * parameters_.get_g() 
						* time_step / parameters_.get_dxdydz(1);
			}

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				buffer[k] = flowField_.v[map(i,j,k)];
			}

			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {		
				flowField_.v[map(i,j,k)] = buffer[k] ;
			}

			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.v[map(i,j,k)]=0.0;
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(0,j,k)]=flowField_.v[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.v[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//back
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(i,0,k)]=0;
		}
	}
	//front
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(i,parameters_.get_num_cells(1)+1,k)]=0;
		}
	}
}
