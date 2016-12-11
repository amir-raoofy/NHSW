#include "Simulation.h"
#include <numeric>

void Simulation::InitDelta(){
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDelta()[i][j] = flowField_.GetEtta()[i][j]-
			( (1-parameters_.get_theta()) * parameters_.get_time_step() / parameters_.get_dxdydz(0) ) *
			(  std::inner_product(flowField_.GetDzI()[i  ][j].begin(), flowField_.GetDzI()[i  ][j].end(), flowField_.GetU()[i  ][j].begin(), 0.0)-
			   std::inner_product(flowField_.GetDzI()[i-1][j].begin(), flowField_.GetDzI()[i-1][j].end(), flowField_.GetU()[i-1][j].begin(), 0.0)  )-
			( (1-parameters_.get_theta()) * parameters_.get_time_step() / parameters_.get_dxdydz(1) ) *
			(  std::inner_product(flowField_.GetDzJ()[i][j  ].begin(), flowField_.GetDzJ()[i][j  ].end(), flowField_.GetV()[i][j  ].begin(), 0.0)-
			   std::inner_product(flowField_.GetDzJ()[i][j-1].begin(), flowField_.GetDzJ()[i][j-1].end(), flowField_.GetV()[i][j-1].begin(), 0.0)  );

		}
	}
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetDelta()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	//TODO boundary is set to zero at the moment

}
