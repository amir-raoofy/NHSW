#include "Simulation.h"

void Simulation::InitDzI(){
	// dz(i+0.5,j,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i+0.5,j,k) = dz 
	// dz(i+0.5,j,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	for (int i = 0; i < parameters_.get_num_cells(0)-1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			flowField_.SetDzI()[i][j].push_back(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j]+1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzI()[i][j].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzI()[i][j].push_back(  	parameters_.get_dxdydz(2) *
						 ( ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2))-
			 	floor  ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
		}
	}
	// same formula for the right boundary but the right boundary buffers are replaced appropriately.
	for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			flowField_.SetDzI()[parameters_.get_num_cells(0)-1][j].push_back(   parameters_.get_dxdydz(2) *
				(  1	- ( ceil(( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )-
										   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
			for (int k = flowField_.Getm()[parameters_.get_num_cells(0)-1][j]+1; k < flowField_.GetM()[parameters_.get_num_cells(0)-1][j]; k++) {
				flowField_.SetDzI()[parameters_.get_num_cells(0)-1][j].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzI()[parameters_.get_num_cells(0)-1][j].push_back(	  parameters_.get_dxdydz(2)*
					   (  ((flowField_.GetEtta()[parameters_.get_num_cells(0)-1][j] +flowField_.GetEttaBoundaries()[1][j])/2 + parameters_.GetHeight() )/ parameters_.get_dxdydz(2)-
				floor( ((flowField_.GetEtta()[parameters_.get_num_cells(0)-1][j] +flowField_.GetEttaBoundaries()[1][j])/2 + parameters_.GetHeight() )/ parameters_.get_dxdydz(0) )  )   );
	}

	//test the initializattion:
	/*
	 *for (int i = 0; i < parameters_.get_num_cells(0); i++) {
	 *  for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	 *    for (int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++) {
	 *        std::cout << "i=" << i << ", j="<< j << ", k="<< k << std::endl;
	 *        std::cout << flowField_.GetDzI()[i][j][k] << std::endl;
	 *    }
	 *  }
	 *}
	 */
}

void Simulation::InitDzJ(){
	// dz(i,j+0.5,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i,j+0.5,k) = dz 
	// dz(i,j+0.5,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)-1; j++) {
			flowField_.SetDzJ()[i][j].push_back(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j]+1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzJ()[i][j].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzJ()[i][j].push_back(  	parameters_.get_dxdydz(2) *
						 ( ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i][j+1])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2))-
			 	floor  ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i][j+1])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
		}
	}
	// same formula for the right boundary but the right boundary buffers are replaced appropriately.
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
			flowField_.SetDzJ()[i][parameters_.get_num_cells(1)-1].push_back(   parameters_.get_dxdydz(2) *
				(  1	- ( ceil(( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )-
										   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )  )   );
			for (int k = flowField_.Getm()[i][parameters_.get_num_cells(1)-1]+1; k < flowField_.GetM()[i][parameters_.get_num_cells(1)-1]; k++) {
				flowField_.SetDzJ()[i][parameters_.get_num_cells(1)-1].push_back(parameters_.get_dxdydz(2));
			}
			flowField_.SetDzJ()[i][parameters_.get_num_cells(1)-1].push_back(	  parameters_.get_dxdydz(2)*
					   (  ((flowField_.GetEtta()[i][parameters_.get_num_cells(1)-1] +flowField_.GetEttaBoundaries()[3][i])/2 + parameters_.GetHeight() )/ parameters_.get_dxdydz(2)-
				floor( ((flowField_.GetEtta()[i][parameters_.get_num_cells(1)-1] +flowField_.GetEttaBoundaries()[3][i])/2 + parameters_.GetHeight() )/ parameters_.get_dxdydz(0) )  )   );
	}

	//test the initializattion:
	/*
	 *for (int i = 0; i < parameters_.get_num_cells(0); i++) {
	 *  for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	 *    for (int k = flowField_.Getm()[i][j]; k <= flowField_.GetM()[i][j]; k++) {
	 *        std::cout << "i=" << i << ", j="<< j << ", k="<< k << std::endl;
	 *        std::cout << flowField_.GetDzJ()[i][j][k] << std::endl;
	 *    }
	 *  }
	 *}
	 */
}
