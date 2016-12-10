#include "Simulation.h"

void Simulation::InitGI(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetGI()[i][j].push_back
				(
					(
					//convection terms
					 flowField_.GetU() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i-1][j][k]) / parameters_.get_dxdydz(0)
					+flowField_.GetV() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i][j-1][k]) / parameters_.get_dxdydz(1)
					+flowField_.GetV() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i][j][k-1]) / ( (flowField_.GetDzI()[i][j][k]+flowField_.GetDzI()[i][j][k-1])/2 )
					//horizontal diffusion terms
					+parameters_.get_viscosity() * (flowField_.GetU()[i+1][j][k] - 2 * flowField_.GetU()[i][j][k] + flowField_.GetU()[i-1][j][k]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_viscosity() * (flowField_.GetU()[i][j+1][k] - 2 * flowField_.GetU()[i][j][k] + flowField_.GetU()[i][j-1][k]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(0)) * (flowField_.GetEtta()[i+1][j]-flowField_.GetEtta()[i][j]) * parameters_.get_g()
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(0)) * (flowField_.GetQ()[i+1][j][k]-flowField_.GetQ()[i][j][k])
					) * flowField_.GetDzI()[i][j][k]
				);
			}
		int k = flowField_.GetM()[i][j] - flowField_.Getm()[i][j];
			flowField_.SetGI()[i][j][k] += parameters_.get_gamma_t() * parameters_.get_time_step() * parameters_.get_u_a();
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetGI()[0][j].push_back(0.0);
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetGI()[parameters_.get_num_cells(0)+1][j].push_back(0.0);
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetGI()[i][0].push_back(0.0);
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetGI()[i][parameters_.get_num_cells(0)+1].push_back(0.0);
		}
	}
	//@test
	std::cout << "print GI" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << "i= " << i << "j= " << j << ":\t";
			for (int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				std::cout << flowField_.GetGI()[i][j][k] << "\t";
			}
			std::cout << std::endl;
		}
	}
}


