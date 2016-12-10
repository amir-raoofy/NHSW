#include "Simulation.h"

void Simulation::InitDzI(){
	// dz(i+0.5,j,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i+0.5,j,k) = dz 
	// dz(i+0.5,j,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzI()[i][j].push_back(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzI()[i][j].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzI()[i][j].push_back(  	parameters_.get_dxdydz(2) *
						 ( ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2))-
			 	floor  ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
		}
	}

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetDzI()[0][j].push_back(flowField_.GetDzI()[1][j][k]);
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetDzI()[parameters_.get_num_cells(0)+1][j].push_back(flowField_.GetDzI()[parameters_.get_num_cells(0)][j][k]);
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetDzI()[i][0].push_back(flowField_.GetDzI()[i][1][k]);
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetDzI()[i][parameters_.get_num_cells(0)+1].push_back(flowField_.GetDzI()[i][parameters_.get_num_cells(0)][k]);
		}
	}
	//@test the initializattion:
	std::cout << "test DzI" << std::endl;
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int k =0; k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j]; k++) {
					std::cout << "i=" << i << ", j="<< j << ", k="<< k << std::endl;
					std::cout << flowField_.GetDzI()[i][j][k] << std::endl;
			}
		}
	}
}

void Simulation::InitDzJ(){
	// dz(i,j+0.5,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i,j+0.5,k) = dz 
	// dz(i,j+0.5,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzJ()[i][j].push_back(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzJ()[i][j].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzJ()[i][j].push_back(  	parameters_.get_dxdydz(2) *
						 ( ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2))-
			 	floor  ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
		}
	}

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]; k++) {
			flowField_.SetDzJ()[0][j].push_back(flowField_.GetDzJ()[1][j][k]);
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]; k++) {
			flowField_.SetDzJ()[parameters_.get_num_cells(0)+1][j].push_back(flowField_.GetDzJ()[parameters_.get_num_cells(0)][j][k]);
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]; k++) {
			flowField_.SetDzJ()[i][0].push_back(flowField_.GetDzJ()[i][1][k]);
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]; k++) {
			flowField_.SetDzJ()[i][parameters_.get_num_cells(0)+1].push_back(flowField_.GetDzJ()[i][parameters_.get_num_cells(0)][k]);
		}
	}
	//@test the initializattion:
	std::cout << "test DzJ" << std::endl;
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int k =0; k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j]; k++) {
					std::cout << "i=" << i << ", j="<< j << ", k="<< k << std::endl;
					std::cout << flowField_.GetDzJ()[i][j][k] << std::endl;
			}
		}
	}

}
