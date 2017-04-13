#include "Solver.h"
#include <algorithm>

JacobiSolverQ::JacobiSolverQ(const Parameters& parameters, FlowField& flowField):
	IterativeSolver(parameters, flowField),
	Q_old_(flowField.GetQ()){
		std::cout << "\033[1;31m====Jacobi solver for non-hydrostatic pressure is invoked====\033[0m"	<< std::endl;
	}

void JacobiSolverQ::updateDomain(){
	
	FLOAT alpha = parameters_.get_theta() * time_step / (parameters_.get_dxdydz(0) 	* parameters_.get_dxdydz(0)	);
	FLOAT beta  = parameters_.get_theta() * time_step / (parameters_.get_dxdydz(1) 	* parameters_.get_dxdydz(0)	);
	FLOAT gamma = parameters_.get_theta() * time_step;

	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int k = 1; k <= flowField_.GetM()[i][j] - flowField_.Getm()[i][j]; k++) {
				flowField_.SetQ()[i][j][k] =(	 alpha * flowField_.GetDzI()[i][j][k] * Q_old_[i+1][j][k] + alpha * flowField_.GetDzI()[i-1][j][k] * Q_old_[i-1][j][k]		//old values
																		 + beta  * flowField_.GetDzJ()[i][j][k] * Q_old_[i][j+1][k] + beta  * flowField_.GetDzJ()[i][j-1][k] * Q_old_[i][j-1][k]
																		 + gamma / flowField_.GetDzK()[i][j][k] * Q_old_[i][j][k+1] + gamma / flowField_.GetDzK()[i][j][k-1] * Q_old_[i][j][k-1]
																		 - (flowField_.GetDzI()[i][j][k]* flowField_.GetU()[i][j][k] - flowField_.GetDzI()[i-1][j][k]* flowField_.GetU()[i-1][j][k] ) / parameters_.get_dxdydz(0) //rhs
																		 - (flowField_.GetDzJ()[i][j][k]* flowField_.GetV()[i][j][k] - flowField_.GetDzJ()[i][j-1][k]* flowField_.GetV()[i][j-1][k] ) / parameters_.get_dxdydz(1)
																		 - (flowField_.GetW()[i][j][k] - flowField_.GetW()[i][j][k-1])
																		)/ (alpha * flowField_.GetDzI()[i][j][k] + alpha * flowField_.GetDzI()[i-1][j][k] //old values
																			 +beta  * flowField_.GetDzJ()[i][j][k] + beta  * flowField_.GetDzJ()[i][j-1][k]
																		 	 +gamma / flowField_.GetDzK()[i][j][k] + alpha / flowField_.GetDzK()[i][j][k-1]
																			 );
			}
		}
	}
}

void JacobiSolverQ::updateBoundary(){		//TODO implement the boundary conditions spcially the top and bottom
	// Boundary
	//left
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int k = 0; k < flowField_.GetM()[0][j] - flowField_.Getm()[0][j]+1; k++) {
			//flowField_.SetQ()[0][j][k]=flowField_.SetQ()[1][j][k];
			flowField_.SetQ()[0][j][k]=0;
		}
	}
	//right
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int k = 0; k < flowField_.GetM()[parameters_.get_num_cells(0)+1][j] - flowField_.Getm()[parameters_.get_num_cells(0)+1][j]+1; k++) {
			//flowField_.SetQ()[parameters_.get_num_cells(0)+1][j][k]=flowField_.SetQ()[parameters_.get_num_cells(0)][j][k];
			flowField_.SetQ()[parameters_.get_num_cells(0)+1][j][k]=0;
		}
	}
	//back
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][0] - flowField_.Getm()[i][0]+1; k++) {
			//flowField_.SetQ()[i][0][k]=flowField_.GetQ()[i][1][k];
			flowField_.SetQ()[i][0][k]=0;
		}
	}
	//front
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int k = 0; k < flowField_.GetM()[i][parameters_.get_num_cells(1)+1] - flowField_.Getm()[i][parameters_.get_num_cells(1)+1]+1; k++) {
			//flowField_.SetQ()[i][parameters_.get_num_cells(1)+1][k]=flowField_.GetQ()[i][parameters_.get_num_cells(1)][k];
			flowField_.SetQ()[i][parameters_.get_num_cells(1)+1][k]=0;
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			flowField_.SetQ()[i][j][0]=0;
		}
	}
	//top

			
	/*	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.SetEtta()[0][j]=flowField_.GetEtta()[1][j];								//left
		flowField_.SetEtta()[parameters_.get_num_cells(0)+1][j]=flowField_.GetEtta()[parameters_.get_num_cells(0)][j];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.SetEtta()[i][0]=flowField_.GetEtta()[i][1];								//bottom
		flowField_.SetEtta()[i][parameters_.get_num_cells(1)+1]=flowField_.GetEtta()[i][parameters_.get_num_cells(1)];	//top
	}
	*/
}

void JacobiSolverQ::updateError(){		//TODO implement error calculation
	/*
	error_.clear();
	std::transform(Q_old_.begin(), Q_old_.end(), flowField_.GetQ().begin(), std::back_inserter(error_), 
		[&](const DiscreteLine& a, const DiscreteLine& b) -> DiscreteLine
		{DiscreteLine c; std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(c), std::minus<FLOAT>()); return c;});
	err_= sqrt ( std::inner_product(error_.begin(), error_.end(), error_.begin(), 0.0,
		std::plus<FLOAT>(), [&](const DiscreteLine& a, const DiscreteLine& b) -> FLOAT
		{return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);}) );
	*/
	//TODO check the implementation of 2d the difference and innerproduct for performance and memory val vs ref
}

void JacobiSolverQ::iterate(){
	updateDomain();
	updateBoundary();
	updateError();
	Q_old_.swap(flowField_.SetQ());
}
void JacobiSolverQ::solve(){
	int i=0;
	err_ = 1;
	while (err_>TOL_ && i<MaxIt_){
		iterate();
		i++;
	}
	if (i==MaxIt_)
		std::cout << "\033[1;31mWARNING\033[0m: solver did not converge; maximum number of iterations was reached." << std::endl;
	else
		std::cout << "Jacobi solver converged after " << i << " iterations, the value of error is "<< err_ << std::endl;
}
