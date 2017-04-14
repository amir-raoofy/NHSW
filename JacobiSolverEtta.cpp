#include "Solver.h"
#include <algorithm>
#include <numeric>

JacobiSolverEtta::JacobiSolverEtta(const Parameters& parameters, FlowField& flowField, Scenario& scenario):
	IterativeSolver(parameters, flowField),
	etta_old_(new FLOAT [(parameters_.get_num_cells(0)+2) * (parameters_.get_num_cells(1)+2)]),
	scenario_(scenario){
		//std::cout << "\033[1;31m====Jacobi solver for etta is invoked====\033[0m"	<< std::endl;
	}

void JacobiSolverEtta::updateDomain(){
	FLOAT alpha =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (time_step * time_step  	)
	 / (parameters_.get_dxdydz(0) 	* parameters_.get_dxdydz(0)			);
	FLOAT beta =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (time_step * time_step  	)
	 / (parameters_.get_dxdydz(1) 	* parameters_.get_dxdydz(1)			);
	FLOAT kappa =
		parameters_.get_theta()
	 * (time_step )
	 / (parameters_.get_dxdydz(0) );
	FLOAT lambda =
		parameters_.get_theta()
	 * (time_step )
	 / (parameters_.get_dxdydz(1) );

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.etta[map(i,j)] =
			(  alpha * flowField_.zaz_i[map(i,j)] * etta_old_[map(i+1,j)]		//old values
				+alpha * flowField_.zaz_i[map(i-1,j)] * etta_old_[map(i-1,j)]
				+beta  * flowField_.zaz_j[map(i,j)] * etta_old_[map(i,j+1)]
				+beta  * flowField_.zaz_j[map(i,j-1)] * etta_old_[map(i,j-1)]
				+ flowField_.delta[map(i,j)]																//rhs terms
				-kappa * flowField_.zag_i[map(i,j)]
				+kappa * flowField_.zag_i[map(i-1,j)]
				-lambda* flowField_.zag_j[map(i,j)]
				+lambda* flowField_.zag_j[map(i,j-1)]	) /
			(1+alpha * flowField_.zaz_i[map(i,j)]												// coeff of unknown
			  +alpha * flowField_.zaz_i[map(i-1,j)]
			  +beta  * flowField_.zaz_j[map(i,j)]
				+beta  * flowField_.zaz_j[map(i,j-1)]); 
		}
	}	
}

void JacobiSolverEtta::updateBoundary(){

	scenario_.updateBoundariesEtta();

}

void JacobiSolverEtta::updateError(){
		
	err_=0;
	for (int i = 0; i < (parameters_.get_num_cells(0)+2) * (parameters_.get_num_cells(1)+2); i++) {
		err_+=(flowField_.etta[i]-etta_old_[i])*(flowField_.etta[i]-etta_old_[i]);
	}

}

void JacobiSolverEtta::iterate(){

	updateDomain();
	updateBoundary();
	updateError();
	swap(flowField_.etta,etta_old_);

}
void JacobiSolverEtta::solve(){

	FLOAT* temp = flowField_.etta;
	int i=0;
	err_ = 1;
	for (int i = 0; i < (parameters_.get_num_cells(0)+2) * (parameters_.get_num_cells(1)+2); i++) {
		etta_old_[i]=flowField_.etta[i];
	}
	while (err_>TOL_*TOL_ && i<MaxIt_){
		iterate();
		i++;
	}
	swap(flowField_.etta,temp);

	if (i==MaxIt_)
		std::cout << "\033[1;31mWARNING\033[0m: solver did not converge; maximum number of iterations was reached." << std::endl;
	else{
		//std::cout << "Jacobi solver converged after " << i << " iterations, the value of error is "<< err_ << std::endl;
	}
}
