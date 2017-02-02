#include "Simulation.h"
#include "Solver.h"
#include <algorithm>

void Simulation::InitW(){
	//Domain + Boundary	
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for(int k = 0; k < parameters_.get_num_cells(2); k++){
				flowField_.SetW()[i][j][k]=0.0;
			}
		}
	}

	//@test
	std::cout << "initialized velocity; W:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetV()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
}

void Simulation::UpdateCellNumberW(){
	//Adjust the cell numbers
	//Domain and boundary
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			while (flowField_.GetW()[i][j].size() < (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetW()[i][j].push_back(0.0);
			}
			while (flowField_.GetW()[i][j].size() > (unsigned)(flowField_.GetM()[i][j] - flowField_.Getm()[i][j] + 1)) {
				flowField_.SetW()[i][j].pop_back();
			}
		}
	}
}

void Simulation::FirstStepUpdateW(){
	//calculation
	DiscreteLine rhs;
	DiscreteLine buffer;
	JacobiSolverAK solver(parameters_, flowField_, buffer, rhs);
	solver.SetParameters (0.00001,1000);

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
/*			for(int k = 0; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++){
					flowField_.SetW()[i][j][k]=10.0;
				}
				*/
						/*
			rhs.clear();
			std::transform(		flowField_.GetDzK()[i][j].begin(),flowField_.GetDzK()[i][j].end(), std::back_inserter(rhs), std::bind1st(std::multiplies<FLOAT>(),
			(flowField_.GetEtta()[i+1][j]-flowField_.GetEtta()[i][j]) * parameters_.get_theta() * parameters_.get_g() * parameters_.get_time_step() / parameters_.get_dxdydz(0)		));
			std::transform(flowField_.GetGK()[i][j].begin(), flowField_.GetGK()[i][j].end(), rhs.begin(), rhs.begin(), std::minus<FLOAT>());
			
			rhs=flowField_.GetGK()[i][j];
			buffer = flowField_.SetW()[i][j];
			solver.SetRhs(rhs);
			solver.SetBuffer(buffer);
			solver.SetIndices(i,j);
			solver.solve();

			flowField_.SetW()[i][j] = buffer;
			*/

			//divegence free w
			for (int k = flowField_.GetM()[i][j] + 1; k < parameters_.get_num_cells(2); k++) {
				flowField_.SetW()[i][j][k]=0.0;
			}
			flowField_.SetW()[i][j][flowField_.Getm()[i][j]]=0.0;			//low boundary
			for(int k = flowField_.Getm()[i][j]+1; k <= flowField_.GetM()[i][j] ; k++){ //domain and the top boundary
				flowField_.SetW()[i][j][k]=flowField_.GetW()[i][j][k-1] - (flowField_.GetU()[i][j][k]*flowField_.GetDzI()[i][j][k]-flowField_.GetU()[i-1][j][k]*flowField_.GetDzI()[i-1][j][k])/parameters_.get_dxdydz(0)
																																- (flowField_.GetV()[i][j][k]*flowField_.GetDzJ()[i][j][k]-flowField_.GetV()[i][j-1][k]*flowField_.GetDzJ()[i][j-1][k])/parameters_.get_dxdydz(1);
			}
			//flowField_.SetW()[i][j][flowField_.GetM()[i][j]]=flowField_.GetW()[i][j][flowField_.GetM()[i][j] -1];		//top boundary
	

		}
	}

	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetW()[0][j][k]=flowField_.GetW()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetW()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetW()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetW()[i][0][k]=flowField_.GetW()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.SetW()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetW()[i][parameters_.get_num_cells(0)][k];
		}
	}
	//@test
	std::cout << "first step velocity update; W:" << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= flowField_.GetM()[i][j]-flowField_.Getm()[i][j] ) {
				std::cout << flowField_.GetW()[i][j][k] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
	//TODO
}

void Simulation::SecondStepUpdateW(){
	//Domain
	//divegence free w
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetW()[i][j][0]=0.0;			//low boundary
			for(int k = 1; k < flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++){
				flowField_.SetW()[i][j][k]=flowField_.GetW()[i][j][k-1] - (flowField_.GetU()[i][j][k]*flowField_.GetDzI()[i][j][k]-flowField_.GetU()[i-1][j][k]*flowField_.GetDzI()[i-1][j][k])/parameters_.get_dxdydz(0)
																																- (flowField_.GetV()[i][j][k]*flowField_.GetDzJ()[i][j][k]-flowField_.GetV()[i][j-1][k]*flowField_.GetDzJ()[i][j-1][k])/parameters_.get_dxdydz(1);
					flowField_.SetW()[i][j][flowField_.GetM()[i][j] - flowField_.Getm()[i][j]]=flowField_.GetW()[i][j][flowField_.GetM()[i][j] - flowField_.Getm()[i][j]-1];		//top boundary
					flowField_.SetW()[i][j][flowField_.GetM()[i][j] - flowField_.Getm()[i][j]]-=( flowField_.GetM()[i][j]<=flowField_.GetM()[i-1][j] )?
									(flowField_.GetU()[i][j][k]*flowField_.GetDzI()[i][j][k]-flowField_.GetU()[i-1][j][k]*flowField_.GetDzI()[i-1][j][k])/parameters_.get_dxdydz(0):
									(flowField_.GetU()[i][j][k]*flowField_.GetDzI()[i][j][k]-parameters_.get_u_a()*flowField_.GetDzI()[i][j][k])/parameters_.get_dxdydz(0);			
					flowField_.SetW()[i][j][flowField_.GetM()[i][j] - flowField_.Getm()[i][j]]-=( flowField_.GetM()[i][j]<=flowField_.GetM()[i][j-1] )?
									(flowField_.GetV()[i][j][k]*flowField_.GetDzJ()[i][j][k]-flowField_.GetV()[i][j-1][k]*flowField_.GetDzJ()[i][j-1][k])/parameters_.get_dxdydz(1):
									(flowField_.GetV()[i][j][k]*flowField_.GetDzJ()[i][j][k]-parameters_.get_v_a()*flowField_.GetDzJ()[i][j][k])/parameters_.get_dxdydz(1);

			}
		}
	}
	/*we do not do this	
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 1; k < flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetW()[i][j][k]=flowField_.GetW()[i][j][k] - parameters_.get_theta() * parameters_.get_time_step() / parameters_.get_dxdydz(0)  * (flowField_.GetQ()[i][j][k+1] - flowField_.GetQ()[i][j][k]);
			}
		}
	}
	*/
	// Boundary
	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]+1; k++) {
			flowField_.SetW()[0][j][k]=flowField_.GetW()[1][j][k];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]+1; k++) {
			flowField_.SetW()[parameters_.get_num_cells(0)+1][j][k]=flowField_.GetW()[parameters_.get_num_cells(0)][j][k];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]+1; k++) {
			flowField_.SetW()[i][0][k]=flowField_.GetW()[i][1][k];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(0)+1] - flowField_.Getm()[i][parameters_.get_num_cells(0)+1]+1; k++) {
			flowField_.SetW()[i][parameters_.get_num_cells(0)+1][k]=flowField_.GetW()[i][parameters_.get_num_cells(0)][k];
		}
	}
}		//TODO check
