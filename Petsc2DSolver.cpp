#include "Solver.h"

Petsc2DSolver::Petsc2DSolver(const Parameters& parameters, FlowField& flowField)
	:PetscSolver(parameters, flowField){
	
	n=parameters_.GetBlockSize2d();
	//create matrix
	MatCreate(PETSC_COMM_WORLD,&A);
	MatSetSizes(A,n,n,PETSC_DECIDE,PETSC_DECIDE);
	MatSetType(A,MATMPIAIJ);
	MatSetFromOptions(A);
	MatMPIAIJSetPreallocation(A,5,NULL,5,NULL);
	//MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
	MatSeqAIJSetPreallocation(A,5,NULL);
	//MatSeqSBAIJSetPreallocation(A,1	,3,NULL);
	MatSetOption(A, MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
	MatGetOwnershipRange(A,&Istart,&Iend);

	VecCreate(PETSC_COMM_WORLD,&b);
	VecSetSizes(b,n,PETSC_DECIDE);
	VecSetFromOptions(b);
	VecDuplicate(b,&x);
	VecSet(x,0.0);

	KSPCreate(PETSC_COMM_WORLD,&ksp);

	PC pc;
	KSPGetPC(ksp, &pc);
	PCSetType(pc, PCJACOBI);
	//PCSetType(pc, PCSOR);

	//KSPSetType(ksp,KSPGMRES);
	KSPSetType(ksp,KSPCG);
	KSPSetOperators(ksp,A,A);
	KSPSetInitialGuessNonzero(ksp,PETSC_TRUE);
	KSPSetTolerances(ksp, parameters_.get_tol_2d(), parameters_.get_tol_2d(),PETSC_DEFAULT, parameters_.get_max_it_2d());
	KSPSetFromOptions(ksp);
}

Petsc2DSolver::~Petsc2DSolver(){
}

void Petsc2DSolver::updateMat(){
	FLOAT alpha =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (time_step * time_step  	)
	 / (parameters_.get_dxdydz(0) 	* parameters_.get_dxdydz(0)			);
	FLOAT beta =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (time_step * time_step  	)
	 / (parameters_.get_dxdydz(1) 	* parameters_.get_dxdydz(1)			);
	
	//std::cout << "my rank is: " << parameters_.topology.id << ", I am writing my portion of global matrix, Istart: " << Istart << " ,Iend:" << Iend << std::endl;

 	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			J = Ii;
			v = 1+alpha * flowField_.zaz_i[map(i,j)]
				 +alpha * flowField_.zaz_i[map(i-1,j)]
		 	 	 +beta  * flowField_.zaz_j[map(i,j)]
		 	 	 +beta  * flowField_.zaz_j[map(i,j-1)]; 
		
			//considering the Nueman bounary condition at real boundareis	
			if ( parameters_.topology.right_id ==-1 && i==parameters_.get_num_cells(0) ) {
				v -=alpha * flowField_.zaz_i[map(i,j)];
			}

			if ( parameters_.topology.left_id ==-1 && i==1 ) {
				v -=alpha * flowField_.zaz_i[map(i-1,j)]; 
			}

			if ( parameters_.topology.front_id ==-1 && j==parameters_.get_num_cells(1 ) ) {
				v -=beta  * flowField_.zaz_j[map(i,j)];
			}

			if ( parameters_.topology.back_id ==-1 && j==1 ) {
				v -=beta  * flowField_.zaz_j[map(i,j-1)];
			}

			MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			
			//inner domain elements
			J=Ii+1;
			if ( i!=parameters_.get_num_cells(0) ) {
				v = -alpha * flowField_.zaz_i[map(i,j)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii-1;
			if ( i!=1 ) {
				v = -alpha * flowField_.zaz_i[map(i-1,j)]; 
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii+parameters_.get_num_cells(0);
			if ( j!=parameters_.get_num_cells(1) ) {
				v = -beta  * flowField_.zaz_j[map(i,j)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}
			
			J=Ii-parameters_.get_num_cells(0);
			if ( j!=1 ) {
				v = -beta  * flowField_.zaz_j[map(i,j-1)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			//domain coupling
			J=Ii +1 - parameters_.get_num_cells(0) + parameters_.topology.npy * parameters_.GetBlockSize2d();
			if ( parameters_.topology.right_id !=-1 && i==parameters_.get_num_cells(0) ) {
				v = -alpha * flowField_.zaz_i[map(i,j)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii -1 + parameters_.get_num_cells(0) - parameters_.topology.npy * parameters_.GetBlockSize2d();
			if ( parameters_.topology.left_id !=-1 && i==1 ) {
				v = -alpha * flowField_.zaz_i[map(i-1,j)]; 
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii+parameters_.get_num_cells(0);
			if ( parameters_.topology.front_id !=-1 && j==parameters_.get_num_cells(1 ) ) {
				v = -beta  * flowField_.zaz_j[map(i,j)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}
			
			J=Ii-parameters_.get_num_cells(0);
			if ( parameters_.topology.back_id !=-1 && j==1 ) {
				v = -beta  * flowField_.zaz_j[map(i,j-1)];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

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
void Petsc2DSolver::updateRHS(){
	
	FLOAT kappa =
		parameters_.get_theta()
	 * (time_step )
	 / (parameters_.get_dxdydz(0) );
	FLOAT lambda =
		parameters_.get_theta()
	 * (time_step )
	 / (parameters_.get_dxdydz(1) );

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			v=  		 flowField_.delta[map(i,j)]
				-kappa * flowField_.zag_i[map(i,j)]
				+kappa * flowField_.zag_i[map(i-1,j)]
				-lambda* flowField_.zag_j[map(i,j)]
				+lambda* flowField_.zag_j[map(i,j-1)];
			VecSetValues(b,1,&Ii,&v,INSERT_VALUES);

	   	}
	}

	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	//VecView(b,PETSC_VIEWER_DRAW_WORLD);
	//getchar();

}

void Petsc2DSolver::solve(){
	
	FLOAT start=MPI::Wtime(); //time measurement	
	
	KSPSolve(ksp,b,x);

	time_+=MPI::Wtime()-start;// time measurment

	KSPGetIterationNumber(ksp,&its);
	it_+=its;

}

void Petsc2DSolver::updateField(){
	
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			VecGetValues(x,1,&Ii,&v);
			flowField_.etta[map(i,j)]=v;
		}
	}


	//VecResetArray(b);

}
