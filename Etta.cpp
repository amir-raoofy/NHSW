#include "Simulation.h" 

void Simulation::InitEtta(){
	/*
	 *	initialization for oscilation scenario
	 */
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			flowField_.SetEtta()[i][j] = -0.1 + (i+0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
		}
	}
	//test the initialization of initial water elevation
	/*
	 *for (int j = 0; j < parameters_.get_num_cells(1); j++) {
	 *  for (int i = 0; i < parameters_.get_num_cells(0); i++) {
	 *    std::cout << flowField_.GetEtta()[i][j] << "\t";
	 *  }
	 *  std::cout << std::endl;
	 *}
	 */
}

void Simulation::InitEttaBoundaries(){ //[left=0; right=1 -> j/y ]; [bottom=2; top=3-> i/x]; [back=4; fornt=5-> k/z]
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		flowField_.SetEttaBoundaries()[2][i]=-0.1 + (i+0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
		flowField_.SetEttaBoundaries()[3][i]=-0.1 + (i+0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
	}

	for (int i = 0; i < parameters_.get_num_cells(1); i++) {
		flowField_.SetEttaBoundaries()[0][i]=-0.1 + (-1 +														 0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
		flowField_.SetEttaBoundaries()[1][i]=-0.1 + (parameters_.get_num_cells(0) +  0.5) * parameters_.get_dxdydz(0)/(5.0 * parameters_.GetCubeLength(0));
	}
	
	//test the initialization of initial water elevation boundaries
/*
 *  for (int i = 0; i < parameters_.get_num_cells(1); i++) {
 *    std::cout << flowField_.GetEttaBoundaries()[0][i] << "\t";
 *  }
 *  std::cout << std::endl;
 *
 *  for (int i = 0; i < parameters_.get_num_cells(1); i++) {
 *    std::cout << flowField_.GetEttaBoundaries()[1][i] << "\t";
 *  }
 *  std::cout << std::endl;
 *
 *  for (int i = 0; i < parameters_.get_num_cells(0); i++) {
 *    std::cout << flowField_.GetEttaBoundaries()[2][i] << "\t";
 *  }
 *  std::cout << std::endl;
 *
 *  for (int i = 0; i < parameters_.get_num_cells(0); i++) {
 *    std::cout << flowField_.GetEttaBoundaries()[3][i] << "\t";
 *  }
 *  std::cout << std::endl;
 */

 }
