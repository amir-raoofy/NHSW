#include "Solver.h"

Petsc1DSolverU::Petsc1DSolverU(const Parameters& parameters, FlowField& flowField):
	Petsc1DSolver(parameters, flowField){}

Petsc1DSolverU::~Petsc1DSolverU(){}

//DONE copy z to right handside
void Petsc1DSolverU::updateRHS(){
	//VecPlaceArray(b, RHS_+(map(i,j,0)));
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		
		v = flowField_.g_i[map(i,j,k)] - flowField_.dz_i[map(i,j,k)]
			*(flowField_.etta[map(i+1,j)]-flowField_.etta[map(i,j)]) 
			*parameters_.get_theta() * parameters_.get_g() 
			* time_step / parameters_.get_dxdydz(0);
		VecSetValues(x,1,&k, &v,INSERT_VALUES);
		VecSetValues(b,1,&k, &v,INSERT_VALUES);

	}

	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	VecAssemblyBegin(x);
	VecAssemblyEnd(x);

}

void Petsc1DSolverU::updateField(FLOAT* resultField){
	
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		VecGetValues(x,1,&k,&v);
		 resultField[map(i,j,k)] = v ;
	}

	//VecResetArray(b);
}
