#include "Simulation.h"

void Simulation::InitM(){
	// M(i+0.5,j) = height + floor ( etta(i+0.5,j) )
	// D
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.M[map(i,j)] =ceil( ( parameters_.GetHeight() + (flowField_.etta[map(i,j)]+ flowField_.etta[map(i+1,j)])/2 )
										 									 / parameters_.get_dxdydz(2) ) -1;
		}
	}
	// B
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.M[map(0,j)]=flowField_.M[map(1,j)];								//left
		flowField_.M[map(parameters_.get_num_cells(0)+1,j)]=flowField_.M[map(parameters_.get_num_cells(0),j)];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.M[map(i,0)]=flowField_.M[map(i,1)];								//bottom
		flowField_.M[map(i,parameters_.get_num_cells(1)+1)]=flowField_.M[map(i,parameters_.get_num_cells(1))];	//top
	}
	//@test
}

void Simulation::UpdateM(){InitM();}
