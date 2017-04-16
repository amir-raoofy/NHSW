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

void PetscSolver::setParameters(FLOAT TOL, int MaxIt){TOL_=TOL; MaxIt_=MaxIt;}
