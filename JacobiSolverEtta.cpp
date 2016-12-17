#include "Solver.h"
#include <algorithm>

JacobiSolverEtta::JacobiSolverEtta(const Parameters& parameters, FlowField& flowField):
	IterativeSolver(parameters, flowField),
	etta_old_(flowField.GetEtta()){
		std::cout << "\033[1;31m====Jacobi solver for etta is invoked====\033[0m"	<< std::endl;
	}

void JacobiSolverEtta::updateDomain(){
	FLOAT alpha =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (parameters_.get_time_step() * parameters_.get_time_step()  	)
	 / (parameters_.get_dxdydz(0) 	* parameters_.get_dxdydz(0)			);
	FLOAT beta =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (parameters_.get_time_step() * parameters_.get_time_step()  	)
	 / (parameters_.get_dxdydz(1) 	* parameters_.get_dxdydz(1)			);
	FLOAT kappa =
		parameters_.get_theta()
	 * (parameters_.get_time_step() )
	 / (parameters_.get_dxdydz(0) );
	FLOAT lambda =
		parameters_.get_theta()
	 * (parameters_.get_time_step() )
	 / (parameters_.get_dxdydz(1) );

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			flowField_.SetEtta()[i][j] =
			(  alpha * flowField_.GetZAZI()[i  ][j] * etta_old_[i+1][j]		//old values
				+alpha * flowField_.GetZAZI()[i-1][j] * etta_old_[i-1][j]
				+beta  * flowField_.GetZAZJ()[i][j  ] * etta_old_[i][j+1]
				+beta  * flowField_.GetZAZJ()[i][j-1] * etta_old_[i][j-1]
				+ flowField_.GetDelta()[i][j]																//rhs terms
				-kappa * flowField_.GetZAGI()[i  ][j]
				+kappa * flowField_.GetZAGI()[i-1][j]
				-lambda* flowField_.GetZAGJ()[i][j  ]
				+lambda* flowField_.GetZAGJ()[i][j-1]	) /
			(1+alpha * flowField_.GetZAZI()[i  ][j]												// coeff of unknown
			  +alpha * flowField_.GetZAZI()[i-1][j]
			  +beta  * flowField_.GetZAZJ()[i][j  ]
				+beta  * flowField_.GetZAZJ()[i][j-1]); 
		}
	}	
}

void JacobiSolverEtta::updateBoundary(){
	// B
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.SetEtta()[0][j]=flowField_.GetEtta()[1][j];								//left
		flowField_.SetEtta()[parameters_.get_num_cells(0)+1][j]=flowField_.GetEtta()[parameters_.get_num_cells(0)][j];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.SetEtta()[i][0]=flowField_.GetEtta()[i][1];								//bottom
		flowField_.SetEtta()[i][parameters_.get_num_cells(1)+1]=flowField_.GetEtta()[i][parameters_.get_num_cells(1)];	//top
	}
}

void JacobiSolverEtta::updateError(){
	error_.clear();
	std::transform(etta_old_.begin(), etta_old_.end(), flowField_.GetEtta().begin(), std::back_inserter(error_), 
		[&](const DiscreteLine& a, const DiscreteLine& b) -> DiscreteLine
		{DiscreteLine c; std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(c), std::minus<FLOAT>()); return c;});
	err_= sqrt ( std::inner_product(error_.begin(), error_.end(), error_.begin(), 0.0,
		std::plus<FLOAT>(), [&](const DiscreteLine& a, const DiscreteLine& b) -> FLOAT
		{return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);}) );
	//TODO check the implementation of 2d the difference and innerproduct for performance and memory val vs ref
}

void JacobiSolverEtta::iterate(){
	updateDomain();
	updateBoundary();
	updateError();
	etta_old_.swap(flowField_.SetEtta());
}
void JacobiSolverEtta::solve(){
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
