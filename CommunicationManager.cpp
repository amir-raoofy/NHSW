#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){}

CommunicationManager::~CommunicationManager(){}

void CommunicationManager::updateRightNeighbour(){

	send_buffer=1;
	recv_buffer=0;

	if (parameters_.topology.right_id!=-1)  {
		MPI::COMM_WORLD.Send(&send_buffer, 1, MPI::INT, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(&recv_buffer, 1, MPI::INT, parameters_.topology.left_id, 0);
	}

	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i)	
		std::cout << "my rank is :  " << parameters_.topology.id 
				 		<< "\trecv buff is: "	<< recv_buffer <<	std::endl;
	}
		
}

void CommunicationManager::updateLeftNeighbour(){

	send_buffer=1;
	recv_buffer=0;

	if (parameters_.topology.left_id!=-1)  {
		MPI::COMM_WORLD.Send(&send_buffer, 1, MPI::INT, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(&recv_buffer, 1, MPI::INT, parameters_.topology.right_id, 0);
	}

	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i)	
		std::cout << "my rank is :  " << parameters_.topology.id 
				 		<< "\trecv buff is: "	<< recv_buffer <<	std::endl;
	}
		
}

void CommunicationManager::updateFrontNeighbour(){

	send_buffer=1;
	recv_buffer=0;

	if (parameters_.topology.front_id!=-1)  {
		MPI::COMM_WORLD.Send(&send_buffer, 1, MPI::INT, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(&recv_buffer, 1, MPI::INT, parameters_.topology.back_id, 0);
	}

	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i)	
		std::cout << "my rank is :  " << parameters_.topology.id 
				 		<< "\trecv buff is: "	<< recv_buffer <<	std::endl;
	}
		
}

void CommunicationManager::updateBackNeighbour(){

	send_buffer=1;
	recv_buffer=0;

	if (parameters_.topology.back_id!=-1)  {
		MPI::COMM_WORLD.Send(&send_buffer, 1, MPI::INT, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(&recv_buffer, 1, MPI::INT, parameters_.topology.front_id, 0);
	}

	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i)	
		std::cout << "my rank is :  " << parameters_.topology.id 
				 		<< "\trecv buff is: "	<< recv_buffer <<	std::endl;
	}
		
}
