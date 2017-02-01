#include "Solver.h"
#include <algorithm>    // std::transform
#include <functional>   // std::plus

JacobiSolverAI::JacobiSolverAI(const Parameters& parameters, FlowField& flowField, DiscreteLine& x, DiscreteLine& rhs):
	IterativeSolver(parameters, flowField),
	rhs_(rhs),
	x_(x),
	x_old_(x),
	error_(){
		std::cout << "\033[1;31m====Jacobi solver for inv [A(i,j)] is invoked====\033[0m"	<< std::endl;
	}

void JacobiSolverAI::updateDomain(){
	const	DiscreteLine& DzI=flowField_.GetDzI()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();
	
	for (int k = flowField_.Getm()[i_][j_]+1; k <flowField_.GetM()[i_][j_] ; k++) {
			x_old_[k] = (	(coeff / ( (DzI[k] + DzI[k-1])/2 )  )	*	x_[k-1] +
									(	 coeff / ( (DzI[k] + DzI[k+1])/2 )  )	*	x_[k+1] + rhs_[k]		) /
									(	 coeff / ( (DzI[k] + DzI[k-1])/2 )    					+
									 	 coeff / ( (DzI[k] + DzI[k+1])/2 ) 							+ DzI[k] );
	}
	
}

void JacobiSolverAI::updateBoundary(){
	const	DiscreteLine& DzI=flowField_.GetDzI()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

	int k;
	k=flowField_.GetM()[i_][j_];
	x_old_[k] =	( (	 coeff / ( (DzI[k] + DzI[k-1])/2 )  )	*	x_[k-1] + rhs_[k]	) /
								(	 coeff / ( (DzI[k] + DzI[k-1])/2 ) 							+ DzI[k] + 
									 parameters_.get_gamma_t() * parameters_.get_sim_time()   );
 	k=flowField_.Getm()[i_][j_];
	x_old_[k] = ( (	 coeff / ( (DzI[k] + DzI[k+1])/2 )  )	*	x_[k+1] + rhs_[k]	) /
								(	 coeff / ( (DzI[k] + DzI[k+1])/2 ) 							+ DzI[k] + 
									 parameters_.get_gamma_b() * parameters_.get_sim_time()   );									 
}

void JacobiSolverAI::updateError(){
	error_.clear();
	std::transform(x_.begin(),x_.end(),x_old_.begin(),std::back_inserter(error_),std::minus<FLOAT>());
	err_= sqrt (std::inner_product(error_.begin(), error_.end(), error_.begin(), 0.0) );
	//std::cout << err_ << std::endl;
}

void JacobiSolverAI::iterate(){
	updateDomain();
	updateBoundary();
	updateError();
	x_.swap(x_old_);
}
void JacobiSolverAI::solve(){
	int i=0;
	err_ = 1;
	while (err_>TOL_ && i<MaxIt_){
		iterate();
		i++;
	}
	if (i==MaxIt_)
		std::cout << "\033[1;31mWARNING\033[0m: solver did not converge; maximum number of iterations was reached." << std::endl;
//	else
//		std::cout << "Jacobi solver converged after " << i << " iterations, the value of error is "<< err_ << std::endl;
}

void JacobiSolverAI::SetIndices(int i, int j){i_=i; j_=j;}
void JacobiSolverAI::SetRhs(DiscreteLine& rhs){rhs_=rhs;}
void JacobiSolverAI::SetBuffer(DiscreteLine& x){x_=x, x_old_=x;}
