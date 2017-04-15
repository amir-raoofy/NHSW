#include "Solver.h"

JacobiSolverAJ::JacobiSolverAJ(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old):
	JacobiSolverAI(parameters, flowField, rhs, x, x_old){}

JacobiSolverAJ::~JacobiSolverAJ(){}

void JacobiSolverAJ::updateDomain(){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();
	//TODO implement appropriate m and M for (i, j+0.5)	
	for (int k = flowField_.m[map(i,j)]+1; k <flowField_.M[map(i,j)]; k++) {
			x_old_[k] = (	(coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k-1)])/2 )  )	*	x_[k-1] +
									(	 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k+1)])/2 )  )	*	x_[k+1] + rhs_[k]		) /
									(	 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k-1)])/2 )    					+
									 	 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k+1)])/2 ) 							+ flowField_.dz_j[map(i,j,k)] );
	}
}

void JacobiSolverAJ::updateBoundary(){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

	int k;
	k=flowField_.M[map(i,j)];
	x_old_[k] = 	(   (	 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k-1)])/2 )  )	*	x_[k-1] + rhs_[k]	) /
						( 		 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k-1)])/2 ) 							+ flowField_.dz_j[map(i,j,k)] + 
									 parameters_.get_gamma_t() * parameters_.get_sim_time()   );
 	k=flowField_.m[map(i,j)];
	x_old_[k] = 	(   (	 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k+1)])/2 )  )	*	x_[k+1] + rhs_[k]	) /
						( 		 coeff / ( (flowField_.dz_j[map(i,j,k)] + flowField_.dz_j[map(i,j,k+1)])/2 ) 							+ flowField_.dz_j[map(i,j,k)] + 
									 parameters_.get_gamma_b() * parameters_.get_sim_time()   );									 
}
