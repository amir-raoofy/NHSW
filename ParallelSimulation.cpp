#include "ParallelSimulation.h"
#include "defaultScenario.h"

ParallelSimulation::ParallelSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Simulation(parameters, flowField, communicationManager)	{
			
		rhs_= new FLOAT [parameters_.get_num_cells(2)];
		x_= new FLOAT [parameters_.get_num_cells(2)];
		x_old_= new FLOAT [parameters_.get_num_cells(2)];
		solver_1d_Ai_ = new JacobiSolverAI(parameters_, flowField_, rhs_, x_, x_old_);
		solver_1d_Aj_ = new JacobiSolverAI(parameters_, flowField_, rhs_, x_, x_old_);
		etta_solver_ = new ParallelJacobiSolverEtta(parameters_, flowField_, communicationManager_ , *scenario_);
		solver_1d_Ai_ ->SetParameters (parameters_.get_tol_1d(),parameters_.get_max_it_1d());
		solver_1d_Aj_ ->SetParameters (parameters_.get_tol_1d(),parameters_.get_max_it_1d());
		etta_solver_  ->SetParameters (parameters_.get_tol_2d(),parameters_.get_max_it_2d());

}

ParallelSimulation::~ParallelSimulation(){

	delete [] rhs_;
	delete [] x_;
	delete [] x_old_;
	delete solver_1d_Ai_;
	delete solver_1d_Aj_;
	delete etta_solver_;

}

void ParallelSimulation::setMeasuredData(){

	it1_= (solver_1d_Ai_ -> get_iterations() ) + ( solver_1d_Aj_ -> get_iterations() );
	it2_= etta_solver_ -> get_iterations();

	T1_= (solver_1d_Ai_ -> get_spent_time() ) + ( solver_1d_Aj_ -> get_spent_time() );
	T2_= etta_solver_ -> get_spent_time();

}
