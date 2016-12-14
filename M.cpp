#include "Simulation.h"

void Simulation::InitM(){
	// M(i+0.5,j) = height + floor ( etta(i+0.5,j) )
	// D
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetM()[i][j] =ceil( ( parameters_.GetHeight() + (flowField_.GetEtta()[i][j]+ flowField_.GetEtta()[i+1][j])/2 )
										 									 / parameters_.get_dxdydz(2) ) -1;
		}
	}
	// B
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.SetM()[0][j]=flowField_.GetM()[1][j];								//left
		flowField_.SetM()[parameters_.get_num_cells(0)+1][j]=flowField_.GetM()[parameters_.get_num_cells(0)][j];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.SetM()[i][0]=flowField_.GetM()[i][1];								//bottom
		flowField_.SetM()[i][parameters_.get_num_cells(1)+1]=flowField_.GetM()[i][parameters_.get_num_cells(1)];	//top
	}
	//@test
	std::cout << "print M" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetM()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
