#include "Simulation.h"

// M(i+0.5,j) = height + floor ( etta(i+0.5,j) )
void Simulation::InitM(){
	for (int i = 0; i < parameters_.get_num_cells(0)-1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			flowField_.SetM()[i][j] = ceil( ( parameters_.GetHeight() + (flowField_.GetEtta()[i][j]+ flowField_.GetEtta()[i+1][j])/2 )
										 									 / parameters_.get_dxdydz(2) );
		}
	}

	// M(i+0.5,j) = height + floor ( etta(i+0.5,j) )
	// same formula for the right boundary but the appropriate buffer is used
	for (int j = 0; j < parameters_.get_num_cells(1); j++) {
		flowField_.SetM()[parameters_.get_num_cells(0)-1][j] =  
			ceil( ( parameters_.GetHeight() + (flowField_.GetEtta()[parameters_.get_num_cells(0)-1][j] 
																			+	flowField_.GetEttaBoundaries()[1][j])/2 )
									 									 / parameters_.get_dxdydz(2) );
	}

	/*
	 *for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	 *  for (int i = 0; i < parameters_.get_num_cells(0); i++) {
	 *    std::cout << flowField_.GetM()[i][j] << "\t";
	 *  }
	 *  std::cout << std::endl;
	 *}
	 */
}
