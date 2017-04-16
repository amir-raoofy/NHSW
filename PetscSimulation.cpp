#include "PetscSimulation.h"
#include "defaultScenario.h"

PetscSimulation::PetscSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Simulation(parameters, flowField, communicationManager)	{

		PetscInitialize(0, NULL,0,NULL);
		petsc_solver_1d_Ai_ 	= new Petsc1DSolver (parameters_, flowField_);
		petsc_solver_1d_Aj_ 	= new Petsc1DSolver (parameters_, flowField_);
		petsc_solver_1d_u_Ai_ 	= new Petsc1DSolverU(parameters_, flowField_);
		petsc_solver_1d_v_Aj_ 	= new Petsc1DSolverV(parameters_, flowField_);
		etta_solver_ 			= new Petsc2DSolver (parameters_, flowField_);

}


PetscSimulation::~PetscSimulation(){

	delete petsc_solver_1d_Ai_;
	delete petsc_solver_1d_Aj_;
	delete petsc_solver_1d_u_Ai_;
	delete petsc_solver_1d_v_Aj_;
	delete etta_solver_;
	PetscFinalize();

}
