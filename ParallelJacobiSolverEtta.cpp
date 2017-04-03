#include "Solver.h"
#include <algorithm>
#include <mpi.h>

ParallelJacobiSolverEtta::ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager): JacobiSolverEtta(parameters, flowField), communicationManager_(communicationManager){}

void ParallelJacobiSolverEtta::iterate(){
	
	updateDomain();
	updateBoundary();
	MPI_Barrier(parameters_.topology.communicator);
	communicationManager_.communicteEtta();
	MPI_Barrier(parameters_.topology.communicator);
	//updateError();
	parallelUpdateError();
	etta_old_.swap(flowField_.SetEtta());

}

void ParallelJacobiSolverEtta::parallelUpdateError(){

	FLOAT recv_buffer;

	this->updateError();
	MPI::COMM_WORLD.Allreduce(&err_, &recv_buffer, 1, MPI::DOUBLE, MPI::MAX); 
	err_ = recv_buffer;

}

