#include "Simulation.h"
#include "defaultScenario.h"

Simulation::Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager)
	{
		time_step=parameters_.get_time_step();
		scenario_ = new defaultScenario(parameters,flowField, communicationManager);
		rhs_= new FLOAT [parameters_.get_num_cells(2)];
		x_= new FLOAT [parameters_.get_num_cells(2)];
		x_old_= new FLOAT [parameters_.get_num_cells(2)];
		solver_1d_Ai_ = new JacobiSolverAI(parameters_, flowField_, rhs_, x_, x_old_);
		solver_1d_Aj_ = new JacobiSolverAJ(parameters_, flowField_, rhs_, x_, x_old_);
		petsc_solver_1d_Ai_ = new Petsc1DSolver(parameters_, flowField_);
		petsc_solver_1d_Aj_ = new Petsc1DSolver(parameters_, flowField_);
		petsc_solver_1d_u_Ai_ = new Petsc1DSolverU(parameters_, flowField_);
		petsc_solver_1d_v_Aj_ = new Petsc1DSolverV(parameters_, flowField_);
	
	}


Simulation::~Simulation(){

	delete scenario_;
	delete [] rhs_;
	delete [] x_;
	delete [] x_old_;
	delete solver_1d_Ai_;
	delete solver_1d_Aj_;

	delete petsc_solver_1d_Ai_;
	delete petsc_solver_1d_Aj_;
	delete petsc_solver_1d_u_Ai_;
	delete petsc_solver_1d_v_Aj_;
}
