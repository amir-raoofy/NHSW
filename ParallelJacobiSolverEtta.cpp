#include "Solver.h"
#include <algorithm>

ParallelJacobiSolverEtta::ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager): JacobiSolverEtta(parameters, flowField), communicationManager_(communicationManager){}

void ParallelJacobiSolverEtta::iterate(){
	updateDomain();
	updateBoundary();
	communicationManager_.communicteEtta();
	MPI_Barrier(parameters_.topology.communicator);
	//updateError();
	//etta_old_.swap(flowField_.SetEtta());
}

