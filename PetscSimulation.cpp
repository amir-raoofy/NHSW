#include "PetscSimulation.h"
#include "defaultScenario.h"

PetscSimulation::PetscSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Simulation(parameters, flowField, communicationManager)	{

		petsc_solver_1d_Ai_ 	= new Petsc1DSolver (parameters_, flowField_);
		petsc_solver_1d_Aj_ 	= new Petsc1DSolver (parameters_, flowField_);
		petsc_solver_1d_u_Ai_ 	= new Petsc1DSolverU(parameters_, flowField_);
		petsc_solver_1d_v_Aj_ 	= new Petsc1DSolverV(parameters_, flowField_);
		etta_solver_ 			= new Petsc2DSolver (parameters_, flowField_);

		petsc_solver_1d_Ai_->setParameters (0.00001,1000);
		petsc_solver_1d_Aj_->setParameters (0.00001,1000);
		petsc_solver_1d_u_Ai_->setParameters (0.00001,1000);
		petsc_solver_1d_v_Aj_->setParameters (0.00001,1000);
		//etta_solver_ ->SetParameters (0.00001,1000);
	
	}


PetscSimulation::~PetscSimulation(){

	delete petsc_solver_1d_Ai_;
	delete petsc_solver_1d_Aj_;
	delete petsc_solver_1d_u_Ai_;
	delete petsc_solver_1d_v_Aj_;
	delete etta_solver_;

}
