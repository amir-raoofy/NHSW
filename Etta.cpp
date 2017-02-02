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
			//flowField_.SetEtta()[i][j] = -0.1 + (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));		//TEST 1			WORKS PERFECTLY Hydro
			
			//flowField_.SetEtta()[i][j] = -0.1 + (j-0.5) * parameters_.get_dxdydz(1)/(5.0 * parameters_.GetCubeLength(1));		//TEST2					
			
			//flowField_.SetEtta()[i][j] = -0.1 + (j-0.5) * parameters_.get_dxdydz(1)/(5.0 * parameters_.GetCubeLength(1))/2	//TEST3				
			//																	+ (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0))/2;
			//flowField_.SetEtta()[i][j] = i<=parameters_.get_num_cells(0)/2?0.1:0.0;																					//TEST4: Dam break #1
			//flowField_.SetEtta()[i][j] = i<=parameters_.get_num_cells(0)/2?-0.2:0.2;																					//TEST4: Dam break #2
			//flowField_.SetEtta()[i][j] = i<=parameters_.get_num_cells(0)/2? 0:0.1;																					//TEST4: Dam break #2
			//flowField_.SetEtta()[i][j] = i<=parameters_.get_num_cells(0)/2?-5.5:-4.5;																					//TEST4: Dam break #3
			//flowField_.SetEtta()[i][j] = (i - parameters_.get_num_cells(0)/2 )*(i - parameters_.get_num_cells(0)/2 )+ (j - parameters_.get_num_cells(0)/2)*(j-parameters_.get_num_cells(0)/2)<=(parameters_.get_num_cells(0)*parameters_.get_num_cells(0)+parameters_.get_num_cells(1)*parameters_.get_num_cells(1))/32?0.1:0;																					//TEST4: Dam break #3
			//flowField_.SetEtta()[i][j] = ( (i<9*parameters_.get_num_cells(0)/16 && i>7*parameters_.get_num_cells(0)/16) && (j<9*parameters_.get_num_cells(1)/16 && j>7*parameters_.get_num_cells(1)/16) ) ?0.3:0.1;																					//TEST4: Dam break #3
			flowField_.SetEtta()[i][j] = 0.1* exp( -( ( i - parameters_.get_num_cells(0)/2 ) *  ( i - parameters_.get_num_cells(0)/2 ) * parameters_.get_dxdydz(0) * parameters_.get_dxdydz(0) +( j - parameters_.get_num_cells(1)/2 ) *  ( j - parameters_.get_num_cells(1)/2 ) * parameters_.get_dxdydz(1) * parameters_.get_dxdydz(1) ) );
		}
	}
	//test the initialization of initial water elevation
	std::cout << "test the initialization of initial water elevation" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetEtta()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void Simulation::FirstStepUpdateEtta(){
	JacobiSolverEtta etta_solver(parameters_, flowField_);
	etta_solver.SetParameters (0.00001,1000);
	etta_solver.solve();

	//test the solution of the initial water elevation
	std::cout << "test the solution of the initial water elevation" << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << flowField_.GetEtta()[i][j] << "\t";
		}
		std::cout << std::endl;
	}

}

void Simulation::SecondStepUpdateEtta(){  //TODO check the implementation expecially the index of M and m
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.SetEtta()[i][j] =flowField_.GetEtta()[i][j] + flowField_.GetQ()[i][j][flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ] / parameters_.get_g();
		}
	}

} //TODO implement
