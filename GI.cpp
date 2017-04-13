#include "Simulation.h"

void Simulation::InitGI(){

	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_i[map(i,j,k)]=
					(
					//convection terms
//					 parameters_.get_sim_time()*flowField_.u[map(i,j,k)]
					 flowField_.u[map(i,j,k)]
					+time_step*flowField_.u [map(i,j,k)] * ( (flowField_.u[map(i+1,j,k)]+flowField_.u[map(i,j,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
					+time_step*(flowField_.v [map(i,j,k)]+flowField_.v [map(i+1,j,k)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i+1,j-1,k)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j+1,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+time_step*(flowField_.w [map(i,j,k)]+flowField_.w [map(i+1,j,k)]+flowField_.w [map(i,j,k-1)]+flowField_.w [map(i+1,j,k-1)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k+1)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k-1)])/2 ) / flowField_.dz_i[map(i,j,k)]
					//horizontal diffusion terms
					+time_step*parameters_.get_viscosity() * (flowField_.u[map(i+1,j,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+time_step*parameters_.get_viscosity() * (flowField_.u[map(i,j+1,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (time_step / parameters_.get_dxdydz(0)) * (flowField_.etta[map(i+1,j)]-flowField_.etta[map(i,j)]) * parameters_.get_g()
					) * flowField_.dz_i[map(i,j,k)];
			}
			flowField_.g_i[map(i,j,flowField_.M[map(i,j)])] += parameters_.get_gamma_t() * time_step * parameters_.get_u_a();
		}
	}
	//TODO fix the lower boundary condition k=0 we have k-1 which is problematic

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
//			flowField_.g_i[0][j].push_back(flowField_.g_i[map(1,j,k)]);
			flowField_.g_i[map(0,j,k)]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_i[parameters_.get_num_cells(0)+1][j].push_back(flowField_.g_i[map(parameters_.get_num_cells(0),j,k)]);
			flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=0.0;
			//flowField_.g_i[parameters_.get_num_cells(0)  ][j][k]=0.0;
			//flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_i[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,0,k)]=flowField_.g_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_i[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}

void Simulation::UpdateGI(){
// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_i[map(i,j,k)]=
					(
					//convection terms
//					 parameters_.get_sim_time()*flowField_.u[map(i,j,k)]
					 flowField_.u[map(i,j,k)]
					+time_step*flowField_.u [map(i,j,k)] * ( (flowField_.u[map(i+1,j,k)]+flowField_.u[map(i,j,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)

					+time_step*(flowField_.v [map(i,j,k)]+flowField_.v [map(i+1,j,k)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i+1,j-1,k)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j+1,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+time_step*(flowField_.w [map(i,j,k)]+flowField_.w [map(i+1,j,k)]+flowField_.w [map(i,j,k-1)]+flowField_.w [map(i+1,j,k-1)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k+1)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k-1)])/2 ) / flowField_.dz_i[map(i,j,k)]
					//horizontal diffusion terms
					+time_step*parameters_.get_viscosity() * (flowField_.u[map(i+1,j,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+time_step*parameters_.get_viscosity() * (flowField_.u[map(i,j+1,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (time_step / parameters_.get_dxdydz(0)) * (flowField_.etta[map(i+1,j)]-flowField_.etta[map(i,j)]) * parameters_.get_g()
					) * flowField_.dz_i[map(i,j,k)];
			}
			flowField_.g_i[map(i,j,flowField_.M[map(i,j)])] += parameters_.get_gamma_t() * time_step * parameters_.get_u_a();
			for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.g_i[map(i,j,k)]=0.0;
			}
		}
	}
	//TODO fix the lower boundary condition k=0 we have k-1 which is problematic

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_i[map(0,j,k)]=flowField_.g_i[map(1,j,k)];
			flowField_.g_i[map(0,j,k)]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_i[map(parameters_.get_num_cells(0),j,k)];
			flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=0.0;
			//flowField_.g_i[parameters_.get_num_cells(0)  ][j][k]=0.0;
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,0,k)]=flowField_.g_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_i[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}
