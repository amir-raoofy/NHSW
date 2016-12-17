#include "Simulation.h" 
#include "Solver.h"

void Simulation::InitEtta(){
  /*
   *	initialization for oscilation scenario
   */
	//	TODO how do we initialize boundary, do we do it specifically?
	// D + B
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.SetEtta()[i][j] = -0.1 + (i-0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
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
	JacobiSolverEtta etta_solver(parameters_, flowField_);	//TODO implement the 2d solver
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
