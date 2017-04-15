#include "Solver.h"

Petsc1DSolverV::Petsc1DSolverV(const Parameters& parameters, FlowField& flowField):
	Petsc1DSolverU(parameters, flowField){}

Petsc1DSolverV::~Petsc1DSolverV(){}

//DONE copy z to right handside
void Petsc1DSolverV::updateRHS(){

	//VecPlaceArray(b, RHS_+(map(i,j,0)));
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		
		v = flowField_.g_j[map(i,j,k)] - flowField_.dz_j[map(i,j,k)]
			*(flowField_.etta[map(i,j+1)]-flowField_.etta[map(i,j)]) 
			*parameters_.get_theta() * parameters_.get_g() 
			* time_step / parameters_.get_dxdydz(1);
		VecSetValues(x,1,&k, &v,INSERT_VALUES);
		VecSetValues(b,1,&k, &v,INSERT_VALUES);


	}

	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	VecAssemblyBegin(x);
	VecAssemblyEnd(x);

}
