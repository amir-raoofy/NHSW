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
	KSPSetType(ksp,KSPGMRES);
	KSPSetOperators(ksp,A,A);
	KSPSetInitialGuessNonzero(ksp,PETSC_TRUE);
	KSPSetTolerances(ksp,1.e-2/n,1.e-50,PETSC_DEFAULT,PETSC_DEFAULT);
	KSPSetFromOptions(ksp);
}

Petsc2DSolver::~Petsc2DSolver(){
}

void Petsc2DSolver::updateMat(){
	FLOAT alpha =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (parameters_.get_time_step() * parameters_.get_time_step()  	)
	 / (parameters_.get_dxdydz(0) 	* parameters_.get_dxdydz(0)			);
	FLOAT beta =
	parameters_.get_g()
	 * (parameters_.get_theta() 	  * parameters_.get_theta()  		 	)
	 * (parameters_.get_time_step() * parameters_.get_time_step()  	)
	 / (parameters_.get_dxdydz(1) 	* parameters_.get_dxdydz(1)			);
	
	//std::cout << "my rank is: " << parameters_.topology.id << ", I am writing my portion of global matrix, Istart: " << Istart << " ,Iend:" << Iend << std::endl;

 	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			J = Ii;
			v = 1+alpha * flowField_.GetZAZI()[i  ][j]
				 +alpha * flowField_.GetZAZI()[i-1][j]
		 	 	 +beta  * flowField_.GetZAZJ()[i][j  ]
		 	 	 +beta  * flowField_.GetZAZJ()[i][j-1]; 
		
			//considering the Nueman bounary condition	
			if ( parameters_.topology.right_id ==-1 && i==parameters_.get_num_cells(0) ) {
				v -=alpha * flowField_.GetZAZI()[i  ][j];
			}

			if ( parameters_.topology.left_id ==-1 && i==1 ) {
				v -=alpha * flowField_.GetZAZI()[i-1][j]; 
			}

			if ( parameters_.topology.front_id ==-1 && j==parameters_.get_num_cells(1 ) ) {
				v -=beta  * flowField_.GetZAZJ()[i][j  ];
			}

			if ( parameters_.topology.back_id ==-1 && j==1 ) {
				v -=beta  * flowField_.GetZAZJ()[i][j-1];
			}

			MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);

			J=Ii+1;
			if (parameters_.topology.right_id !=-1 || ( parameters_.topology.right_id ==-1 && i!=parameters_.get_num_cells(0) ) ) {
				v = -alpha * flowField_.GetZAZI()[i  ][j];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii-1;
			if (parameters_.topology.left_id !=-1 || ( parameters_.topology.left_id ==-1 && i!=1 ) ) {
				v = -alpha * flowField_.GetZAZI()[i-1][j]; 
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}

			J=Ii+parameters_.get_num_cells(0);
			if (parameters_.topology.front_id !=-1 || ( parameters_.topology.front_id ==-1 && j!=parameters_.get_num_cells(1) ) ) {
				v = -beta  * flowField_.GetZAZJ()[i][j  ];
				MatSetValues(A,1,&Ii,1,&J,&v,INSERT_VALUES);
			}
			
			J=Ii-parameters_.get_num_cells(0);
			if (parameters_.topology.back_id !=-1 || ( parameters_.topology.back_id ==-1 && j!=1 ) ) {
				v = -beta  * flowField_.GetZAZJ()[i][j-1];
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
	 * (parameters_.get_time_step() )
	 / (parameters_.get_dxdydz(0) );
	FLOAT lambda =
		parameters_.get_theta()
	 * (parameters_.get_time_step() )
	 / (parameters_.get_dxdydz(1) );

	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			v=  		 flowField_.GetDelta()[i][j]
				-kappa * flowField_.GetZAGI()[i  ][j]
				+kappa * flowField_.GetZAGI()[i-1][j]
				-lambda* flowField_.GetZAGJ()[i][j  ]
				+lambda* flowField_.GetZAGJ()[i][j-1];
			VecSetValues(b,1,&Ii,&v,INSERT_VALUES);

	   	}
	}

	VecAssemblyBegin(b);
	VecAssemblyEnd(b);
	//VecView(b,PETSC_VIEWER_DRAW_WORLD);
	//getchar();

}

void Petsc2DSolver::solve(){

	KSPSolve(ksp,b,x);
	KSPGetIterationNumber(ksp,&its);
	//std::cout << "iteration numbers: " << its << std::endl;

}

void Petsc2DSolver::updateField(){
	
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			Ii= (i-1) + (j-1) * parameters_.get_num_cells(0) + parameters_.topology.id * parameters_.GetBlockSize2d();
			VecGetValues(x,1,&Ii,&v);
			flowField_.SetEtta()[i][j]=v;
		}
	}

	// B
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.SetEtta()[0][j]=flowField_.GetEtta()[1][j];								//left
		flowField_.SetEtta()[parameters_.get_num_cells(0)+1][j]=flowField_.GetEtta()[parameters_.get_num_cells(0)][j];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.SetEtta()[i][0]=flowField_.GetEtta()[i][1];								//back
		flowField_.SetEtta()[i][parameters_.get_num_cells(1)+1]=flowField_.GetEtta()[i][parameters_.get_num_cells(1)];	//front
	}

	VecResetArray(b);

}