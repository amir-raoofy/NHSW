#include "Solver.h"

Petsc1DSolver::Petsc1DSolver(const Parameters& parameters, FlowField& flowField, const DiscreteCube& Dz, const DiscreteCube& RHS, DiscreteRectangle& resultField):
	PetscSolver(parameters, flowField),Dz_(Dz),RHS_(RHS), resultField_(resultField){
	
	n=parameters_.get_num_cells(2);
	//create matrix
	MatCreate(PETSC_COMM_SELF,&A);
	MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,n,n);
	MatSetType(A,MATSEQAIJ);
	MatSetFromOptions(A);
	//MatMPIAIJSetPreallocation(A,3,NULL,3,NULL);
	//MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
	MatSeqAIJSetPreallocation(A,3,NULL);
	//MatSeqSBAIJSetPreallocation(A,1	,3,NULL);
	MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
	MatGetOwnershipRange(A,&Istart,&Iend);

	VecCreate(PETSC_COMM_SELF,&b);
	VecSetSizes(b,PETSC_DECIDE,n);
	VecSetFromOptions(b);
	VecDuplicate(b,&x);
	VecSet(x,0.0);

	KSPCreate(PETSC_COMM_SELF,&ksp);
	KSPSetType(ksp,KSPGMRES);
	KSPSetOperators(ksp,A,A);
	KSPSetInitialGuessNonzero(ksp,PETSC_TRUE);
	KSPSetTolerances(ksp,1.e-2/n,1.e-50,PETSC_DEFAULT,PETSC_DEFAULT);
	KSPSetFromOptions(ksp);
}

Petsc1DSolver::~Petsc1DSolver(){
}

//DONE cheat from the iterate function
void Petsc1DSolver::updateMat(){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

 	for (Ii=Istart; Ii<Iend; Ii++) {
		if ( Ii>flowField_.Getm()[i_][j_] && Ii <flowField_.GetM()[i_][j_]) {
			J=Ii-1; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii-1])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii+1; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii+1])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii-1])/2 ) + coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii+1])/2 ) + Dz_[i_][j_][Ii]; MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.Getm()[i_][j_]){
			J=Ii+1; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii+1])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii+1])/2 )	+ Dz_[i_][j_][Ii] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.GetM()[i_][j_]){
			J=Ii-1; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii-1])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[i_][j_][Ii] + Dz_[i_][j_][Ii-1])/2 )	+ Dz_[i_][j_][Ii] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else{
			J=Ii;   v = 1.0; MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
	}
  MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
  MatSetOption(A,MAT_SYMMETRIC,PETSC_TRUE);
	//MatView(A,PETSC_VIEWER_DRAW_WORLD);
	//MatView(A,PETSC_VIEWER_STDOUT_WORLD);
	//getchar();
}

//DONE copy z to right handside
void Petsc1DSolver::updateRHS(){

 	VecPlaceArray(b, RHS_[i_][j_].data());
	/*
	for (Ii=Istart; Ii<Iend; Ii++) {
		v = RHS_[i_][j_][Ii]; VecSetValues(b,1,&Ii,&v,INSERT_VALUES); //TODO optimize this using set more than one value in Petsc
	}
	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	*/
}

//TODO copy result back to the routine
void Petsc1DSolver::solve(){
	KSPSolve(ksp,b,x);
	KSPGetIterationNumber(ksp,&its);
}

void Petsc1DSolver::updateField(){
	VecDot(b,x,&v);
	resultField_[i_][j_]=v;

	VecResetArray(b);
}

void Petsc1DSolver::setIndices(int i, int j){i_=i; j_=j;}
