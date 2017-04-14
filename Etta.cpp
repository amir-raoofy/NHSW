#include "Simulation.h" 
#include "Solver.h"
#include <math.h>

void Simulation::InitEtta(){
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

void Simulation::UpdateEtta(){
	JacobiSolverEtta etta_solver(parameters_, flowField_);
	etta_solver.SetParameters (0.00001,1000);
	etta_solver.set_time_step(time_step);
	etta_solver.solve();

	//considering wet and drying cells
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {

			if (flowField_.etta[map(i,j)] + parameters_.GetHeight()< parameters_.GetDryCellError() ) {
				flowField_.etta[map(i,j)] = -parameters_.GetHeight() + parameters_.GetDryCellError();
			}

		}
	}

}
