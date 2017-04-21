#include "Solver.h"
#include <mpi.h>

JacobiSolverAI::JacobiSolverAI(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old):
	JacobiIterativeSolver1D(parameters, flowField, rhs, x, x_old)
	{
		//std::cout << "\033[1;31m====Jacobi solver for inv [A(i,j)] is invoked====\033[0m"	<< std::endl;
	}

JacobiSolverAI::~JacobiSolverAI(){}

void JacobiSolverAI::updateDomain(){

	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();
	
	for (int k = flowField_.m[map(i,j)]+1; k <flowField_.M[map(i,j)] ; k++) {
			x_old_[k] = (	(coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k-1)])/2 )  )	*	x_[k-1] +
									(	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k+1)])/2 )  )	*	x_[k+1] + rhs_[k]		) /
									(	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k-1)])/2 )    					+
									 	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k+1)])/2 ) 							+ flowField_.dz_i[map(i,j,k)] );
	}
	
}

void JacobiSolverAI::updateBoundary(){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

	int k;
	k=flowField_.M[map(i,j)];
	x_old_[k] =	( (	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k-1)])/2 )  )	*	x_[k-1] + rhs_[k]	) /
								(	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k-1)])/2 ) 							+ flowField_.dz_i[map(i,j,k)] + 
									 parameters_.get_gamma_t() * parameters_.get_sim_time()   );
 	k=flowField_.m[map(i,j)];
	x_old_[k] = ( (	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k+1)])/2 )  )	*	x_[k+1] + rhs_[k]	) /
								(	 coeff / ( (flowField_.dz_i[map(i,j,k)] + flowField_.dz_i[map(i,j,k+1)])/2 ) 							+ flowField_.dz_i[map(i,j,k)] + 
									 parameters_.get_gamma_b() * parameters_.get_sim_time()   );									 
}

void JacobiSolverAI::updateError(){
	err_=0;
	FLOAT norm_x=0;

	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		err_+=(x_[k]-x_old_[k])*(x_[k]-x_old_[k]);
		norm_x+= x_[k]*x_[k];
	}

	err_/=norm_x;
}

void JacobiSolverAI::iterate(){
	updateDomain();
	updateBoundary();
	updateError();
	swap(x_,x_old_);
}

void JacobiSolverAI::solve(){
	//FLOAT* temp = x_;
	int i=0;
	err_ = 1;
	FLOAT start=MPI::Wtime(); //time measurement

	while (err_>TOL_*TOL_ && i<MaxIt_){
		iterate();
		i++;
	}
	
	time_+=MPI::Wtime()-start;
	it_+=i;

	//swap(x_,temp);

	if (i==MaxIt_)
		std::cout << "\033[1;31mWARNING\033[0m: solver did not converge; maximum number of iterations was reached." << std::endl;
//	else
//		std::cout << "Jacobi solver converged after " << i << " iterations, the value of error is "<< err_ << std::endl;

}


