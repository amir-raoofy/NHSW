#include "Solver.h"
#include <algorithm>
#include <mpi.h>
#include"helper.h"

ParallelJacobiSolverEtta::ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager): JacobiSolverEtta(parameters, flowField), communicationManager_(communicationManager){}

void ParallelJacobiSolverEtta::iterate(){
	
	updateDomain();
	updateBoundary();
	MPI_Barrier(parameters_.topology.communicator);
	communicationManager_.communicteEtta();
	parallelUpdateError();
	swap(flowField_.etta,etta_old_);

}

void ParallelJacobiSolverEtta::parallelUpdateError(){

	FLOAT recv_buffer;

	this->updateError();
	MPI::COMM_WORLD.Allreduce(&err_, &recv_buffer, 1, MPI::DOUBLE, MPI::MAX); 
	err_ = recv_buffer;

}

