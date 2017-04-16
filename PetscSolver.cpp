#include "Solver.h"

PetscSolver::PetscSolver(const Parameters& parameters, FlowField& flowField):
	Solver(parameters, flowField){}

PetscSolver::~PetscSolver(){
	/*
	 *KSPDestroy(&ksp);
	 *VecDestroy(&x);
	 *VecDestroy(&b);
	 *MatDestroy(&A);
	 */
}
