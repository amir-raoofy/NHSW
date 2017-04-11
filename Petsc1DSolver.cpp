#include "Solver.h"

Petsc1DSolver::Petsc1DSolver(const Parameters& parameters, FlowField& flowField, FLOAT* Dz, FLOAT* RHS, FLOAT* resultField):
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

	PC pc;
	KSPGetPC(ksp, &pc);
	PCSetType(pc, PCJACOBI);
	//PCSetType(pc, PCSOR);

	//KSPSetType(ksp,KSPGMRES);
	KSPSetType(ksp,KSPCG);
	KSPSetOperators(ksp,A,A);
	KSPSetInitialGuessNonzero(ksp,PETSC_TRUE);
	KSPSetTolerances(ksp,1.e-50,1.e-5,PETSC_DEFAULT,PETSC_DEFAULT);
	KSPSetFromOptions(ksp);
}

Petsc1DSolver::~Petsc1DSolver(){
}

//DONE cheat from the iterate function
void Petsc1DSolver::updateMat(){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

 	for (Ii=Istart; Ii<Iend; Ii++) {
		if ( Ii>flowField_.m[map(i,j)] && Ii <flowField_.M[map(i,j)]) {
			J=Ii-1; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii-1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii+1; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii+1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii-1)])/2 ) + coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii+1)])/2 ) + Dz_[map(i,j,Ii)]; MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.m[map(i,j)]){
			J=Ii+1; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii+1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii+1)])/2 )	+ Dz_[map(i,j,Ii)] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.M[map(i,j)]){
			J=Ii-1; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii-1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz_[map(i,j,Ii)] + Dz_[map(i,j,Ii-1)])/2 )	+ Dz_[map(i,j,Ii)] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
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

	VecPlaceArray(b, RHS_+(map(i,j,0)));
	
	}

void Petsc1DSolver::solve(){
	KSPSolve(ksp,b,x);
	KSPGetIterationNumber(ksp,&its);
}

void Petsc1DSolver::updateField(){
	
	VecDot(b,x,&v);
	resultField_[map(i,j)]=v;

	VecResetArray(b);
}

void Petsc1DSolver::setIndices(int i, int j){this->i=i; this->j=j;}
