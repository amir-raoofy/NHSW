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
			flowField_.SetDzI()[i][j][flowField_.Getm()[i][j]]=(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j] + 1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzI()[i][j][k]=parameters_.get_dxdydz(2);
			}
			flowField_.SetDzI()[i][j][flowField_.GetM()[i][j]]=(  	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
			 	)   );
		 }
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[0][j][k]=flowField_.GetDzI()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzI()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[i][0][k]=flowField_.GetDzI()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzI()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateDzI(){
	// dz(i+0.5,j,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i+0.5,j,k) = dz 
	// dz(i+0.5,j,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzI()[i][j][flowField_.Getm()[i][j]]=    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
			for (int k = flowField_.Getm()[i][j]+1 ; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzI()[i][j][k]=parameters_.get_dxdydz(2);
			}
			flowField_.SetDzI()[i][j][flowField_.GetM()[i][j]]= 	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
				);
			for (int k = flowField_.GetM()[i][j] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.SetDzI()[i][j][k]=0.0;
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[0][j][k]=flowField_.GetDzI()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzI()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[i][0][k]=flowField_.GetDzI()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzI()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzI()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateCellNumberDzI(){
	//Adjust the cell numbers
	//this function just adjust the number of the cells
	//later on the update function should be called to update the values
	//appropriately
	//Domain and boundary
for (int i = 0; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetDzI()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzI()[i][j].back()=parameters_.get_dxdydz(2);
				flowField_.SetDzI()[i][j].push_back(0.0);
			}
			while (flowField_.GetDzI()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzI()[i][j].pop_back();
			}
		}
	}
	//@test
	std::cout << "test DZ" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetDzI()[i][j].size() << "\t";;
		}
		std::cout << std::endl;
	}

			std::cout << "here" << std::endl;
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
			flowField_.SetDzJ()[i][j][flowField_.Getm()[i][j]]=(    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
			for (int k = flowField_.Getm()[i][j] + 1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzJ()[i][j][k] = parameters_.get_dxdydz(2);
			}
			flowField_.SetDzJ()[i][j][flowField_.GetM()[i][j]]=  	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
			 	)   ;
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[0][j][k]=flowField_.GetDzJ()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzJ()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[i][0][k]=flowField_.GetDzJ()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzJ()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateDzJ(){
	// dz(i,j+0.5,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i,j+0.5,k) = dz 
	// dz(i,j+0.5,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzJ()[i][j][flowField_.GetM()[i][j]]=    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
			for (int k = flowField_.Getm()[i][j]+1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzJ()[i][j][k]=parameters_.get_dxdydz(2);
			}
			flowField_.SetDzJ()[i][j][flowField_.GetM()[i][j]]= 	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  ( flowField_.GetEtta()[i][j] +flowField_.GetEtta()[i+1][j])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
				);
			for (int k = flowField_.GetM()[i][j] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.SetDzJ()[i][j][k]=0.0;
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[0][j][k]=flowField_.GetDzJ()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzJ()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[i][0][k]=flowField_.GetDzJ()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzJ()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzJ()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateCellNumberDzJ(){
	//Adjust the cell numbers
	//this function just adjust the number of the cells
	//later on the update function should be called to update the values
	//appropriately
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetDzJ()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzJ()[i][j].back()=parameters_.get_dxdydz(2);
				flowField_.SetDzJ()[i][j].push_back(0.0);
			}
			while (flowField_.GetDzJ()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzJ()[i][j].pop_back();
			}
		}
	}
}

void Simulation::InitDzK(){
	// dz(i,j,k+0.5) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i,j,k+0.5) = dz 
	// dz(i,j,k+0.5) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzK()[i][j][flowField_.Getm()[i][j]]=  parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  );
			for (int k = flowField_.Getm()[i][j] + 1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzK()[i][j][k]=parameters_.get_dxdydz(2);
			}
			flowField_.SetDzK()[i][j][flowField_.GetM()[i][j]] =(  	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  flowField_.GetEtta()[i][j]  + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  flowField_.GetEtta()[i][j]  + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
			 	)   );
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[0][j][k]=flowField_.GetDzK()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzK()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[i][0][k]=flowField_.GetDzK()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzK()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateDzK(){
	// dz(i,j,k+0.5) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i,j,k+0.5) = dz 
	// dz(i,j,k+0.5) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetDzK()[i][j][flowField_.Getm()[i][j]]=    parameters_.get_dxdydz(2) *
				(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
					 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
			for (int k = flowField_.Getm()[i][j]+1; k < flowField_.GetM()[i][j]; k++) {
				flowField_.SetDzK()[i][j][k]=parameters_.get_dxdydz(2);
			}
			flowField_.SetDzK()[i][j][flowField_.GetM()[i][j]]= 	parameters_.get_dxdydz(2) *
				(  1-  ceil( (  flowField_.GetEtta()[i][j] + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  				 ( (  flowField_.GetEtta()[i][j] + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
				);
			for (int k = flowField_.GetM()[i][j] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.SetDzK()[i][j][k]=0.0;
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[0][j][k]=flowField_.GetDzK()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetDzK()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[i][0][k]=flowField_.GetDzK()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetDzK()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetDzK()[i][parameters_.get_num_cells(0)][k];
		}
	}
}

void Simulation::UpdateCellNumberDzK(){
	//Adjust the cell numbers
	//this function just adjust the number of the cells
	//later on the update function should be called to update the values
	//appropriately
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetDzJ()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzJ()[i][j].back()=parameters_.get_dxdydz(2);
				flowField_.SetDzJ()[i][j].push_back(0.0);
			}
			while (flowField_.GetDzJ()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetDzJ()[i][j].pop_back();
			}
		}
	}
}
