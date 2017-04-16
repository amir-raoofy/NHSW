#include "ParallelSimulation.h"
#include "defaultScenario.h"

ParallelSimulation::ParallelSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Simulation(parameters, flowField, communicationManager)	{
			
		rhs_= new FLOAT [parameters_.get_num_cells(2)];
		x_= new FLOAT [parameters_.get_num_cells(2)];
		x_old_= new FLOAT [parameters_.get_num_cells(2)];
		solver_1d_Ai_ = new JacobiSolverAI(parameters_, flowField_, rhs_, x_, x_old_);
		solver_1d_Aj_ = new JacobiSolverAI(parameters_, flowField_, rhs_, x_, x_old_);
		solver_1d_Ai_ ->SetParameters (0.00001,1000);
		solver_1d_Aj_ ->SetParameters (0.00001,1000);

}

ParallelSimulation::~ParallelSimulation(){

	//delete [] rhs_;
	//delete [] x_;
	//delete [] x_old_;
	//delete solver_1d_Ai_;
	//delete solver_1d_Aj_;
}
