#include "defaultScenario.h"

defaultScenario::defaultScenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Scenario(parameters, flowField, communicationManager){}

defaultScenario::~defaultScenario(){}

void defaultScenario::InitEtta(){
  /*
   *	initialization for oscilation scenario
   */
	//	TODO how do we initialize boundary, do we do it specifically?
	// D + B
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			//flowField_.etta[map(i,j)] = -0.1 + (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));		//TEST 1			WORKS PERFECTLY Hydro
			
			//flowField_.etta[map(i,j)] = -0.1 + (j-0.5) * parameters_.get_dxdydz(1)/(5.0 * parameters_.GetCubeLength(1));		//TEST2					
			
			//flowField_.etta[map(i,j)] = -0.1 + (j-0.5) * parameters_.get_dxdydz(1)/(5.0 * parameters_.GetCubeLength(1))/2	//TEST3				
			//																	+ (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0))/2;
			//flowField_.etta[map(i,j)] = i<=parameters_.get_num_cells(0)/2?0.1:0.0;																					//TEST4: Dam break #1
			//flowField_.etta[map(i,j)] = i<=parameters_.get_num_cells(0)/2?-0.2:0.2;																					//TEST4: Dam break #2
			//flowField_.etta[map(i,j)] = i<=parameters_.get_num_cells(0)/2? 0:0.1;																					//TEST4: Dam break #2
			//flowField_.etta[map(i,j)] = i<=parameters_.get_num_cells(0)/2?-5.5:-4.5;																					//TEST4: Dam break #3
			//flowField_.etta[map(i,j)] = (i - parameters_.get_num_cells(0)/2 )*(i - parameters_.get_num_cells(0)/2 )+ (j - parameters_.get_num_cells(0)/2)*(j-parameters_.get_num_cells(0)/2)<=(parameters_.get_num_cells(0)*parameters_.get_num_cells(0)+parameters_.get_num_cells(1)*parameters_.get_num_cells(1))/32?0.1:0;																					//TEST4: Dam break #3
			//flowField_.etta[map(i,j)] = ( (i<9*parameters_.get_num_cells(0)/16 && i>7*parameters_.get_num_cells(0)/16) && (j<9*parameters_.get_num_cells(1)/16 && j>7*parameters_.get_num_cells(1)/16) ) ?0.3:0.1;																					//TEST4: Dam break #3
			
			//flowField_.etta[map(i,j)] = 0.1* exp( -( ( i - parameters_.get_num_cells(0)/2 ) *  ( i - parameters_.get_num_cells(0)/2 ) * parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0) +( j - parameters_.get_num_cells(1)/2 ) *  ( j - parameters_.get_num_cells(1)/2 ) * parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1) ) );

			flowField_.etta[map(i,j)] = 0.1* exp( -( pow (parameters_.topology.id_x * (parameters_.GetCubeLength(0)) / parameters_.topology.npx + i * parameters_.get_dxdydz(0)  - parameters_.GetCubeLength(0)/2	,2) + pow (parameters_.topology.id_y * (parameters_.GetCubeLength(1)) / parameters_.topology.npy + j * parameters_.get_dxdydz(1)  - parameters_.GetCubeLength(1)/2	,2)	 ) );
			//flowField_.etta[map(i,j)] = -1.0 + 2.0 * (i-0.5) * parameters_.get_dxdydz(0) / parameters_.GetCubeLength(0) ;		//works	for dry scenario with gamma_t=0.001
		}
	}

			
	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.etta[map(i,j)] = -parameters_.GetHeight() + parameters_.GetDryCellError() ;
			}

		}
	}

}

void defaultScenario::Initm(){
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.m[map(i,j)] = floor( ( parameters_.GetHeight() - parameters_.GetHeight() )
										 									 / parameters_.get_dxdydz(2) );
		}
	}
}

void defaultScenario::InitM(){
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

void defaultScenario::InitDzI(){
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

void defaultScenario::InitDzJ(){
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

void defaultScenario::InitDzK(){
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

void defaultScenario::InitU(){
	// Domain + Boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.u[map(i,j,k)]=0.0;
			}
		}
	}

}

void defaultScenario::InitV(){
	// Domain + Boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.v[map(i,j,k)]=0.0;
			}
		}
	}
}

void defaultScenario::InitW(){
	//Domain + Boundary	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.w[map(i,j,k)]=0.0;
			}
		}
	}
}

void defaultScenario::InitGI(){

	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_i[map(i,j,k)]=
					(
					//convection terms
//					 parameters_.get_sim_time()*flowField_.u[map(i,j,k)]
					 flowField_.u[map(i,j,k)]
					+parameters_.get_time_step()*flowField_.u [map(i,j,k)] * ( (flowField_.u[map(i+1,j,k)]+flowField_.u[map(i,j,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
					+parameters_.get_time_step()*(flowField_.v [map(i,j,k)]+flowField_.v [map(i+1,j,k)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i+1,j-1,k)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j+1,k)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+parameters_.get_time_step()*(flowField_.w [map(i,j,k)]+flowField_.w [map(i+1,j,k)]+flowField_.w [map(i,j,k-1)]+flowField_.w [map(i+1,j,k-1)])/4 *( (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k+1)])/2 - (flowField_.u[map(i,j,k)]+flowField_.u[map(i,j,k-1)])/2 ) / flowField_.dz_i[map(i,j,k)]
					//horizontal diffusion terms
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.u[map(i+1,j,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.u[map(i,j+1,k)] - 2 * flowField_.u[map(i,j,k)] + flowField_.u[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(0)) * (flowField_.etta[map(i+1,j)]-flowField_.etta[map(i,j)]) * parameters_.get_g()
					) * flowField_.dz_i[map(i,j,k)];
			}
			flowField_.g_i[map(i,j,flowField_.M[map(i,j)])] += parameters_.get_gamma_t() * parameters_.get_time_step() * parameters_.get_u_a();
		}
	}
	//TODO fix the lower boundary condition k=0 we have k-1 which is problematic

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
//			flowField_.g_i[0][j].push_back(flowField_.g_i[map(1,j,k)]);
			flowField_.g_i[map(0,j,k)]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_i[parameters_.get_num_cells(0)+1][j].push_back(flowField_.g_i[map(parameters_.get_num_cells(0),j,k)]);
			flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=0.0;
			//flowField_.g_i[parameters_.get_num_cells(0)  ][j][k]=0.0;
			//flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_i[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,0,k)]=flowField_.g_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_i[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}

void defaultScenario::InitGJ(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_j[map(i,j,k)]=
					(
					//convection terms
//					parameters_.get_sim_time()*flowField_.v[map(i,j,k)]
					flowField_.v[map(i,j,k)]
					+parameters_.get_time_step()*(flowField_.u [map(i,j,k)]+flowField_.u [map(i,j+1,k)]+flowField_.u [map(i-1,j,k)]+flowField_.u [map(i-1,j+1,k)])/4 *( (flowField_.v[map(i,j,k)]+flowField_.v[map(i+1,j,k)])/2 - (flowField_.v[map(i,j,k)]+flowField_.v[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
					+parameters_.get_time_step()*flowField_.v [map(i,j,k)] * ( (flowField_.v[map(i,j+1,k)]+flowField_.v[map(i,j,k)])/2 - (flowField_.v[map(i,j,k)]+flowField_.v[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+parameters_.get_time_step()*(flowField_.w [map(i,j,k)]+flowField_.w [map(i,j+1,k)]+flowField_.w [map(i,j,k-1)]+flowField_.w [map(i,j+1,k-1)])/4 *( (flowField_.v[map(i,j,k)]+flowField_.v[map(i,j,k+1)])/2 - (flowField_.v[map(i,j,k)]+flowField_.v[map(i,j,k-1)])/2 ) / flowField_.dz_j[map(i,j,k)]
//+					 flowField_.u [map(i,j,k)] * (flowField_.v[map(i,j,k)] - flowField_.v[map(i-1,j,k)]) / parameters_.get_dxdydz(0)
//					+flowField_.v [map(i,j,k)] * (flowField_.v[map(i,j,k)] - flowField_.v[map(i,j-1,k)]) / parameters_.get_dxdydz(1)
//					+flowField_.w [map(i,j,k)] * (flowField_.v[map(i,j,k)] - flowField_.v[map(i,j,k-1)]) / ( (flowField_.dz_j[map(i,j,k)]+flowField_.dz_j[map(i,j,k-1)])/2 )
					//horizontal diffusion terms
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.v[map(i+1,j,k)] - 2 * flowField_.v[map(i,j,k)] + flowField_.v[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.v[map(i,j+1,k)] - 2 * flowField_.v[map(i,j,k)] + flowField_.v[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					-(1-parameters_.get_theta()) * (parameters_.get_time_step() / parameters_.get_dxdydz(1)) * (flowField_.etta[map(i,j+1)]-flowField_.etta[map(i,j)]) * parameters_.get_g()
					) * flowField_.dz_j[map(i,j,k)];
			}
			flowField_.g_j[map(i,j,flowField_.M[map(i,j)])] += parameters_.get_gamma_t() * parameters_.get_time_step() * parameters_.get_v_a();
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_j[map(0,j,k)]=flowField_.g_j[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_j[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_j[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_j[i][0].push_back(flowField_.g_j[map(i,1,k)]);
			flowField_.g_j[map(i,0,k)]=0.0;
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_j[i][parameters_.get_num_cells(0)+1].push_back(flowField_.g_j[i][parameters_.get_num_cells(0)][k]);
			flowField_.g_j[map(i,parameters_.get_num_cells(1)+1,k)]=0.0;
			//flowField_.g_j[i][parameters_.get_num_cells(1)  ][k]=0.0;
		}
	}
}

void defaultScenario::InitGK(){
	// Domain (for i and j) but Domain + Boundary for k
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = flowField_.m[map(i,j)]; k <= flowField_.M[map(i,j)] ; k++) {
				flowField_.g_k[map(i,j,k)]=
					(
					//convection terms
//					parameters_.get_sim_time()*flowField_.w[map(i,j,k)]
					flowField_.w[map(i,j,k)]
					+parameters_.get_time_step()*(flowField_.u [map(i,j,k)]+flowField_.u [map(i,j,k+1)]+flowField_.u [map(i-1,j,k)]+flowField_.u [map(i-1,j,k+1)])/4 *( (flowField_.w[map(i+1,j,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i-1,j,k)])/2 ) / parameters_.get_dxdydz(0)
				+parameters_.get_time_step()*(flowField_.v [map(i,j,k)]+flowField_.v [map(i,j,k+1)]+flowField_.v [map(i,j-1,k)]+flowField_.v [map(i,j-1,k+1)])/4 *( (flowField_.w[map(i,j+1,k)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j-1,k)])/2 ) / parameters_.get_dxdydz(1)
					+parameters_.get_time_step()*flowField_.w [map(i,j,k)] * ( (flowField_.w[map(i,j,k+1)]+flowField_.w[map(i,j,k)])/2 - (flowField_.w[map(i,j,k)]+flowField_.w[map(i,j,k-1)])/2 ) / ((flowField_.dz_k[map(i,j,k)]+flowField_.dz_k[map(i,j,k+1)])/2)
									
					//TODO check if it is dz[k] or dz[k-1]
					//horizontal diffusion terms
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.w[map(i+1,j,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i-1,j,k)]) / (parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0))
					+parameters_.get_time_step()*parameters_.get_viscosity() * (flowField_.w[map(i,j+1,k)] - 2 * flowField_.w[map(i,j,k)] + flowField_.w[map(i,j-1,k)]) / (parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1))
					//hydrostatic pressure
					//-parameters_.get_g()*parameters_.get_sim_time()
					) * flowField_.dz_k[map(i,j,k)];
			}
		}
	}
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(0,j,k)]=flowField_.g_k[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_k[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(i,0,k)]=flowField_.g_k[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_k[map(i,parameters_.get_num_cells(1),k)];
		}
	}
}

