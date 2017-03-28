#include "Solver.h"
#include <algorithm>

ParallelJacobiSolverEtta::ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager): JacobiSolverEtta(parameters, flowField), communicationManager_(communicationManager){}

void ParallelJacobiSolverEtta::iterate(){
	communicationManager_.communicteEtta();
	MPI_Barrier(parameters_.topology.communicator);
	updateDomain();
	updateBoundary();
	updateError();
	//etta_old_.swap(flowField_.SetEtta());
}

