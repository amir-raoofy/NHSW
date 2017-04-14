#include "Simulation.h"

void Simulation::InitGK(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_k[map(i,j,k)]=
					(
					//convection terms
//					parameters_.get_sim_time()*flowField_.w[map(i,j,k)]
					flowField_.w[map(i,j,k)]
					+time_step*(flowField_.u [map(i,j,k)]+flowField_.u [map(i,j,k+1)]+flowField_.u [map(i-1,j,k)]+flowField_.u [map(i-1,j,k+1)])/4 *( (flowField_.w[map(i+1,j,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
				+time_step*(flowField_.v [map(i,j,k)]+flowField_.v [map(i,j,k+1)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i,j-1,k+1)])/4 *( (flowField_.w[map(i,j+1,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+time_step*flowField_.w [map(i,j,k)] * ( (flowField_.w[map(i,j,k+1)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j,k-1)])/2 ) / ((flowField_.dz_k[map(i,j,k)]+flowField_.dz_k[map(i,j,k+1)])/2)
									
					//TODO check if it is dz[k] or dz[k-1]
					//horizontal diffusion terms
					+time_step*parameters_.get_viscosity() * (flowField_.w[map(i+1,j,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+time_step*parameters_.get_viscosity() * (flowField_.w[map(i,j+1,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					//-parameters_.get_g()*parameters_.get_sim_time()
					) * flowField_.dz_k[map(i,j,k)];
			}
		}
	}

	scenario_->updateBoundariesGK();

}

void Simulation::UpdateGK(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_k[map(i,j,k)]=
					(
					//convection terms
//					parameters_.get_sim_time()*flowField_.w[map(i,j,k)]
					flowField_.w[map(i,j,k)]
					+time_step*(flowField_.u [map(i,j,k)]+flowField_.u [map(i,j,k+1)]+flowField_.u [map(i-1,j,k)]+flowField_.u [map(i-1,j,k+1)])/4 *( (flowField_.w[map(i+1,j,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
					+time_step*(flowField_.v [map(i,j,k)]+flowField_.v [map(i,j,k+1)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i,j-1,k+1)])/4 *( (flowField_.w[map(i,j+1,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+time_step*flowField_.w [map(i,j,k)] * ( (flowField_.w[map(i,j,k+1)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j,k-1)])/2 ) / ((flowField_.dz_k[map(i,j,k)]+flowField_.dz_k[map(i,j,k+1)])/2)
									
					//TODO check if it is dz[k] or dz[k-1]
					//horizontal diffusion terms
					+time_step*parameters_.get_viscosity() * (flowField_.w[map(i+1,j,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+time_step*parameters_.get_viscosity() * (flowField_.w[map(i,j+1,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					) * flowField_.dz_k[map(i,j,k)];
			}
		}
	}

	scenario_->updateBoundariesGK();

}
