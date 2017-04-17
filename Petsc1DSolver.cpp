#include "Solver.h"

Petsc1DSolver::Petsc1DSolver(const Parameters& parameters, FlowField& flowField):
	PetscSolver(parameters, flowField){
	
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
	KSPSetTolerances(ksp, parameters_.get_tol_1d(), parameters_.get_tol_1d(),PETSC_DEFAULT, parameters_.get_max_it_1d());
	KSPSetFromOptions(ksp);
}

Petsc1DSolver::~Petsc1DSolver(){
}

//DONE cheat from the iterate function
void Petsc1DSolver::updateMat(FLOAT* Dz){
	FLOAT coeff = parameters_.get_vis() * parameters_.get_sim_time();

 	for (Ii=Istart; Ii<Iend; Ii++) {
		if ( Ii>flowField_.m[map(i,j)] && Ii <flowField_.M[map(i,j)]) {
			J=Ii-1; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii-1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii+1; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii+1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii-1)])/2 ) + coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii+1)])/2 ) + Dz[map(i,j,Ii)]; MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.m[map(i,j)]){
			J=Ii+1; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii+1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii+1)])/2 )	+ Dz[map(i,j,Ii)] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else if(Ii==flowField_.M[map(i,j)]){
			J=Ii-1; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii-1)])/2 ); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
			J=Ii  ; v = coeff / ( (Dz[map(i,j,Ii)] + Dz[map(i,j,Ii-1)])/2 )	+ Dz[map(i,j,Ii)] + parameters_.get_gamma_b() * parameters_.get_sim_time(); MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
		else{
			J=Ii;   v = 1.0; MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES); 
		}
	}
  MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
  //MatSetOption(A,MAT_SYMMETRIC,PETSC_TRUE);
	//MatView(A,PETSC_VIEWER_DRAW_WORLD);
	//MatView(A,PETSC_VIEWER_STDOUT_WORLD);
	//getchar();
}

//DONE copy z to right handside
void Petsc1DSolver::updateRHS(FLOAT* RHS){

	//VecPlaceArray(b, RHS_+(map(i,j,0)));
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {

		VecSetValues(x,1,&k,RHS+k,INSERT_VALUES);
        VecSetValues(b,1,&k,RHS+k,INSERT_VALUES);

	}

	VecAssemblyBegin(x);
	VecAssemblyBegin(b);
	VecAssemblyEnd(x);
	VecAssemblyEnd(b);

}

void Petsc1DSolver::solve(){

	FLOAT start=MPI::Wtime(); //time measurement
	
	KSPSolve(ksp,b,x);

	time_+=MPI::Wtime()-start;// time measurment

	KSPGetIterationNumber(ksp,&its);
	it_+=its;

}

void Petsc1DSolver::updateField(FLOAT* resultField, FLOAT* Dz){

	FLOAT s=0;
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		VecGetValues(x,1,&k,&v);
		s+=v*Dz[map(i,j,k)];
	}

	//VecDot(b,x,&v);
	resultField[map(i,j)]=s;

	//VecResetArray(b);
}

void Petsc1DSolver::setIndices(int i, int j){this->i=i; this->j=j;}
