#include "Simulation.h"

void Simulation::InitGK(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetGK()[i][j].push_back
				(
					(
					//convection terms
					 flowField_.GetU() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i-1][j][k]) / parameters_.get_dxdydz(0)
					+flowField_.GetV() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i][j-1][k]) / parameters_.get_dxdydz(1)
					+flowField_.GetW() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i][j][k-1]) / flowField_.GetDzK()[i][j][k] //TODO check if it is dz[k] or dz[k-1]
					//horizontal diffusion terms
					+parameters_.get_viscosity() * (flowField_.GetW()[i+1][j][k] - 2 * flowField_.GetW()[i][j][k] + flowField_.GetW()[i-1][j][k]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_viscosity() * (flowField_.GetW()[i][j+1][k] - 2 * flowField_.GetW()[i][j][k] + flowField_.GetW()[i][j-1][k]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(1)) * (flowField_.GetQ()[i][j][k+1]-flowField_.GetQ()[i][j][k])
					) * flowField_.GetDzK()[i][j][k]
				);
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetGK()[0][j].push_back(0.0);
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetGK()[parameters_.get_num_cells(0)+1][j].push_back(0.0);
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetGK()[i][0].push_back(0.0);
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetGK()[i][parameters_.get_num_cells(0)+1].push_back(0.0);
		}
	}
	//@test the initializattion:
	std::cout << "test initialization of GK" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetGK()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}

void Simulation::UpdateCellNumberGK(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetGK()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetGK()[i][j].push_back(0.0);
			}
			while (flowField_.GetGK()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetGK()[i][j].pop_back();
			}
		}
	}
}

void Simulation::UpdateGK(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetGK()[i][j][k]=
					(
					//convection terms
					 flowField_.GetU() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i-1][j][k]) / parameters_.get_dxdydz(0)
					+flowField_.GetV() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i][j-1][k]) / parameters_.get_dxdydz(1)
					+flowField_.GetW() [i][j][k] * (flowField_.GetW()[i][j][k] - flowField_.GetW()[i][j][k-1]) / flowField_.GetDzK()[i][j][k]  //TODO check if it is dz [k] or dz[k-1]
					//horizontal diffusion terms
					+parameters_.get_viscosity() * (flowField_.GetW()[i+1][j][k] - 2 * flowField_.GetW()[i][j][k] + flowField_.GetW()[i-1][j][k]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_viscosity() * (flowField_.GetW()[i][j+1][k] - 2 * flowField_.GetW()[i][j][k] + flowField_.GetW()[i][j-1][k]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(1)) * (flowField_.GetQ()[i][j][k+1]-flowField_.GetQ()[i][j][k])
					) * flowField_.GetDzK()[i][j][k];
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetGK()[0][j][k]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetGK()[parameters_.get_num_cells(0)+1][j][k]=0.0;
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetGK()[i][0][k]=0.0;
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetGK()[i][parameters_.get_num_cells(0)+1][k]=0.0;
		}
	}
//TODO implementation
}
