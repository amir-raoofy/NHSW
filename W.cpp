#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitW(){
	//Domain + Boundary	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.w[map(i,j,k)]=0.0;
			}
		}
	}
}

void Simulation::UpdateW(){
	//calculation

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

			//divegence free w
			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.w[map(i,j,k)]=0.0;
			}
			flowField_.w[map(i,j,flowField_.m[map(i,j)])]=0.0;			//low boundary
			for(int k = flowField_.m[map(i,j)]+1; k <= flowField_.M[map(i,j)] ; k++){ //domain and the top boundary
				flowField_.w[map(i,j,k)]=flowField_.w[map(i,j,k-1)] - (flowField_.u[map(i,j,k)]*flowField_.dz_i[map(i,j,k)]-flowField_.u[map(i-1,j,k)]*flowField_.dz_i[map(i-1,j,k)])/parameters_.get_dxdydz(0)				- (flowField_.v[map(i,j,k)]*flowField_.dz_j[map(i,j,k)]-flowField_.v[map(i,j-1,k)]*flowField_.dz_j[map(i,j-1,k)])/parameters_.get_dxdydz(1);
			}
			//considering the precipitation
			//flowField_.w[map(i,j,flowField_.M[map(i,j)])]+=parameters_.GetPrecipitation()*flowField_.dz_k[map(i,j,flowField_.M[map(i,j)])];		//top boundary
			//flowField_.w[i][j][flowField_.M()[i][j]]=flowField_.w[i][j][flowField_.M()[i][j] -1];		//top boundary
	

		}
	}

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()<0.001 ) {
				flowField_.w[map(i,j,flowField_.m[map(i,j)])] = 0.0;
			}

		}
	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(0,j,k)]=flowField_.w[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.w[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(i,0,k)]=flowField_.w[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.w[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}
