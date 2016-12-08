#include "StencilInvA.h"

StencilInvA::StencilInvA(const Parameters& parameters,const FlowField& flowField): Stencil( parameters, flowField){}

void StencilInvA::Operate(int i, int j, int k){
		DiscreteLine x(flowField_.GetM()[i][j]-flowField_.Getm()[i][j] + 1, 0);
		for (int c = 0; c < 100; c++) {
			
		x[k] = 
		(
		(	parameters_.get_vis() * parameters_.get_sim_time() / 
		( (flowField_.GetDzI()[i][j][k] + flowField_.GetDzI()[i][j][k+1])/2 )  )
		*	x[k+1]
		+
		(	parameters_.get_vis() * parameters_.get_sim_time() / 
		( (flowField_.GetDzI()[i][j][k] + flowField_.GetDzI()[i][j][k-1])/2 )  )
		*	x[k-1]   
		+
		flowField_.GetDzI()[i][j][k]
		)

		/

		(
		flowField_.GetDzI()[i][j][k]
		+
	 	parameters_.get_vis() * parameters_.get_sim_time() / 
		( (flowField_.GetDzI()[i][j][k] + flowField_.GetDzI()[i][j][k-1])/2 ) 
	 	+
		parameters_.get_vis() * parameters_.get_sim_time() / 
		( (flowField_.GetDzI()[i][j][k] + flowField_.GetDzI()[i][j][k+1])/2 ) 
		);
		std::cout << "i=" << i << " ,j= "<< j << ",k= " << k << ",x= " << x[k] << std::endl;

		}
	}

