#include "Solver.h"

JacobiSolverAJ::JacobiSolverAJ(const Parameters& parameters, FlowField& flowField, DiscreteLine& x):
	JacobiSolverAI(parameters, flowField, x){}

void JacobiSolverAJ::updateDomain(){
	const	DiscreteLine& DzJ=flowField_.GetDzJ()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();
	//TODO implement appropriate m and M for (i, j+0.5)	
	for (int k = 1; k <flowField_.GetM()[i_][j_] - flowField_.Getm()[i_][j_]; k++) {
			x_old_[k] = (		(	 coeff / ( (DzJ[k] + DzJ[k-1])/2 )  )	*	x_[k-1] +
									(	 coeff / ( (DzJ[k] + DzJ[k+1])/2 )  )	*	x_[k+1] + DzJ[k]		) /
									(	 coeff / ( (DzJ[k] + DzJ[k-1])/2 )    					+
									 	 coeff / ( (DzJ[k] + DzJ[k+1])/2 ) 							+ DzJ[k] );
	}
	
}

void JacobiSolverAJ::updateBoundary(){
	const	DiscreteLine& DzJ=flowField_.GetDzJ()[i_][j_];
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

	int k;
	k=flowField_.GetM()[i_][j_] - flowField_.Getm()[i_][j_];
	x_old_[k] = 	(   (	 coeff / ( (DzJ[k] + DzJ[k-1])/2 )  )	*	x_[k-1] + DzJ[k]	) /
						( 		 coeff / ( (DzJ[k] + DzJ[k-1])/2 ) 							+ DzJ[k] + 
									 parameters_.get_gamma_t() * parameters_.get_sim_time()   );
 	k=0;
	x_old_[k] = 	(   (	 coeff / ( (DzJ[k] + DzJ[k+1])/2 )  )	*	x_[k+1] + DzJ[k]	) /
						( 		 coeff / ( (DzJ[k] + DzJ[k+1])/2 ) 							+ DzJ[k] + 
									 parameters_.get_gamma_b() * parameters_.get_sim_time()   );									 
}
