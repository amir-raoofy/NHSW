#include "Solver.h"

JacobiSolverAK::JacobiSolverAK(const Parameters& parameters, FlowField& flowField, DiscreteLine& x, DiscreteLine& rhs):
	JacobiSolverAI(parameters, flowField, x, rhs){}

void JacobiSolverAK::updateDomain(){
	const	DiscreteLine& DzK=flowField_.GetDzK()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();
	//TODO implement appropriate m and M for (i, j+0.5)	
	for (int k = flowField_.Getm()[i_][j_]+1; k <flowField_.GetM()[i_][j_]; k++) {
			x_old_[k] = (	(coeff / ( (DzK[k] + DzK[k-1])/2 )  )	*	x_[k-1] +
									(	 coeff / ( (DzK[k] + DzK[k+1])/2 )  )	*	x_[k+1] + rhs_[k]		) /
									(	 coeff / ( (DzK[k] + DzK[k-1])/2 )    					+
									 	 coeff / ( (DzK[k] + DzK[k+1])/2 ) 							+ DzK[k] );
	}
}

void JacobiSolverAK::updateBoundary(){
	const	DiscreteLine& DzK=flowField_.GetDzK()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

	int k;
	k=flowField_.GetM()[i_][j_];
	x_old_[k] = 	(   (	 coeff / ( (DzK[k] + DzK[k-1])/2 )  )	*	x_[k-1] + rhs_[k]	) /
						( 		 coeff / ( (DzK[k] + DzK[k-1])/2 ) 							+ DzK[k]);
 	k=flowField_.Getm()[i_][j_];
	x_old_[k] = 	(   (	 coeff / ( (DzK[k] + DzK[k+1])/2 )  )	*	x_[k+1] + rhs_[k]	) /
						( 		 coeff / ( (DzK[k] + DzK[k+1])/2 ) 							+ DzK[k]);									 
}
