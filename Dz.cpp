#include "Simulation.h"

void Simulation::InitDzI(){
	// dz(i+0.5,j,k) = dz (1 - ( ceil ( ( height - b ) / dz ) - ( height - b ) / dz ) )
	// dz(i+0.5,j,k) = dz 
	// dz(i+0.5,j,k) = dz ( (etta + height) -floor(etta+height) )
	// in the oscilation scenario b = height
	// case m = M is not yet suppoerted.
	// Domain
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_i[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{
	
		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
				flowField_.dz_i[map(i,j,flowField_.m[map(i,j)])]=(    parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
				for (int k = flowField_.m[map(i,j)] + 1; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_i[map(i,j,k)]=parameters_.get_dxdydz(2);
				}
				flowField_.dz_i[map(i,j,flowField_.M[map(i,j)])]=(  	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
					  				 ( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
				 	)   );
			 }
		}

	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(0,j,k)]=flowField_.dz_i[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_i[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,0,k)]=flowField_.dz_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_i[map(i,parameters_.get_num_cells(1),k)];
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
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_i[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
				flowField_.dz_i[map(i,j,flowField_.m[map(i,j)])]=    parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
				for (int k = flowField_.m[map(i,j)]+1 ; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_i[map(i,j,k)]=parameters_.get_dxdydz(2);
				}
				flowField_.dz_i[map(i,j,flowField_.M[map(i,j)])]= 	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
					  				 ( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
					);
				for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
					flowField_.dz_i[map(i,j,k)]=0.0;
				}

			}
		}

	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(0,j,k)]=flowField_.dz_i[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_i[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,0,k)]=flowField_.dz_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_i[map(i,parameters_.get_num_cells(1),k)];
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
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_j[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
				flowField_.dz_j[map(i,j,flowField_.m[map(i,j)])]=(    parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    );
				for (int k = flowField_.m[map(i,j)] + 1; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_j[map(i,j,k)] = parameters_.get_dxdydz(2);
				}
				flowField_.dz_j[map(i,j,flowField_.M[map(i,j)])]=  	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
					  				 ( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
			 		)   ;
			}
		}

	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(0,j,k)]=flowField_.dz_j[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_j[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,0,k)]=flowField_.dz_j[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_j[map(i,parameters_.get_num_cells(1),k)];
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
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_j[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
				flowField_.dz_j[map(i,j,flowField_.M[map(i,j)])]=    parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
				for (int k = flowField_.m[map(i,j)]+1; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_j[map(i,j,k)]=parameters_.get_dxdydz(2);
				}
				flowField_.dz_j[map(i,j,flowField_.M[map(i,j)])]= 	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
					  				 ( (  ( flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
					);
				for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
					flowField_.dz_j[map(i,j,k)]=0.0;
				}

			}
		}

	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(0,j,k)]=flowField_.dz_j[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_j[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,0,k)]=flowField_.dz_j[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_j[map(i,parameters_.get_num_cells(1),k)];
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
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_k[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_k[map(i,j,flowField_.m[map(i,j)])]=  parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  );
				for (int k = flowField_.m[map(i,j)] + 1; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_k[map(i,j,k)]=parameters_.get_dxdydz(2);
				}
				flowField_.dz_k[map(i,j,flowField_.M[map(i,j)])] =(  	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  flowField_.etta[map(i,j)]  + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
				  					 ( (  flowField_.etta[map(i,j)]  + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
				 	)   );

			}
		}

	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(0,j,k)]=flowField_.dz_k[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_k[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,0,k)]=flowField_.dz_k[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_k[map(i,parameters_.get_num_cells(1),k)];
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
	
	if (parameters_.get_num_cells(2)==1) {

		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_k[map(i,j,flowField_.m[map(i,j)])]= (flowField_.etta[map(i,j)] +flowField_.etta[map(i+1,j)])/2 + parameters_.GetHeight(); 

			}
		}
		
	}else{


		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {

				flowField_.dz_k[map(i,j,flowField_.m[map(i,j)])]=    parameters_.get_dxdydz(2) *
					(  1-(  ceil(   ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)   )-
						 				 		  ( parameters_.GetHeight()-parameters_.GetHeight() ) / parameters_.get_dxdydz(2)	 )  )    ;
				for (int k = flowField_.m[map(i,j)]+1; k < flowField_.M[map(i,j)]; k++) {
					flowField_.dz_k[map(i,j,k)]=parameters_.get_dxdydz(2);
				}
				flowField_.dz_k[map(i,j,flowField_.M[map(i,j)])]= 	parameters_.get_dxdydz(2) *
					(  1-  ceil( (  flowField_.etta[map(i,j)] + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )+
					  				 ( (  flowField_.etta[map(i,j)] + parameters_.GetHeight() ) / parameters_.get_dxdydz(2) )
					);
				for (int k = flowField_.M[map(i,j)] + 1; k < parameters_.get_num_cells(2); k++) {
					flowField_.dz_k[map(i,j,k)]=0.0;
				}

			}
		}

	}


	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(0,j,k)]=flowField_.dz_k[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_k[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,0,k)]=flowField_.dz_k[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_k[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}
