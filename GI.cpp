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
					+flowField_.GetW() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i][j][k-1]) / ( (flowField_.GetDzI()[i][j][k]+flowField_.GetDzI()[i][j][k-1])/2 )
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
	//TODO fix the lower boundary condition k=0 we have k-1 which is problematic

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
	//@test the initializattion:
	std::cout << "test initialization of GI" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetGI()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}

void Simulation::UpdateCellNumberGI(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetGI()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetGI()[i][j].push_back(0.0);
			}
			while (flowField_.GetGI()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetGI()[i][j].pop_back();
			}
		}
	}
}

void Simulation::UpdateGI(){
// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetGI()[i][j][k]=
					(
					//convection terms
					 flowField_.GetU() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i-1][j][k]) / parameters_.get_dxdydz(0)
					+flowField_.GetV() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i][j-1][k]) / parameters_.get_dxdydz(1)
					+flowField_.GetW() [i][j][k] * (flowField_.GetU()[i][j][k] - flowField_.GetU()[i][j][k-1]) / ( (flowField_.GetDzI()[i][j][k]+flowField_.GetDzI()[i][j][k-1])/2 )
					//horizontal diffusion terms
					+parameters_.get_viscosity() * (flowField_.GetU()[i+1][j][k] - 2 * flowField_.GetU()[i][j][k] + flowField_.GetU()[i-1][j][k]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_viscosity() * (flowField_.GetU()[i][j+1][k] - 2 * flowField_.GetU()[i][j][k] + flowField_.GetU()[i][j-1][k]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(0)) * (flowField_.GetEtta()[i+1][j]-flowField_.GetEtta()[i][j]) * parameters_.get_g()
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(0)) * (flowField_.GetQ()[i+1][j][k]-flowField_.GetQ()[i][j][k])
					) * flowField_.GetDzI()[i][j][k];
			}
		int k = flowField_.GetM()[i][j] - flowField_.Getm()[i][j];
			flowField_.SetGI()[i][j][k] += parameters_.get_gamma_t() * parameters_.get_time_step() * parameters_.get_u_a();
		}
	}
	//TODO fix the lower boundary condition k=0 we have k-1 which is problematic

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetGI()[0][j][k]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetGI()[parameters_.get_num_cells(0)+1][j][k]=0.0;
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetGI()[i][0][k]=0.0;
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetGI()[i][parameters_.get_num_cells(0)+1][k]=0.0;
		}
	}
}
