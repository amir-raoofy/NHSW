#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){

	right_send_buffer 	= new FLOAT [parameters_.get_num_cells(1)+2];
	left_send_buffer 		= new FLOAT [parameters_.get_num_cells(1)+2];
	front_send_buffer 	= new FLOAT [parameters_.get_num_cells(0)+2];
	back_send_buffer 		= new FLOAT [parameters_.get_num_cells(0)+2];
	right_recv_buffer 	= new FLOAT [parameters_.get_num_cells(1)+2];
	left_recv_buffer 		= new FLOAT [parameters_.get_num_cells(1)+2];
	front_recv_buffer 	= new FLOAT [parameters_.get_num_cells(0)+2];
	back_recv_buffer 		= new FLOAT [parameters_.get_num_cells(0)+2];
	
}

CommunicationManager::~CommunicationManager(){

	delete [] right_send_buffer;
	delete [] left_send_buffer;
	delete [] front_send_buffer;
	delete [] back_send_buffer;
	delete [] right_recv_buffer;
	delete [] left_recv_buffer;
	delete [] front_recv_buffer;
	delete [] back_recv_buffer;

}

void CommunicationManager::updateRightNeighbour(){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			right_send_buffer[i]=flowField_.GetEtta()[parameters_.get_num_cells(0)][i];
		}
		MPI::COMM_WORLD.Send(right_send_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			flowField_.SetEtta()[0][i]=left_recv_buffer[i];
		}
	}
		
}

void CommunicationManager::updateLeftNeighbour(){

	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			left_send_buffer[i]=flowField_.GetEtta()[1][i];
		}
		MPI::COMM_WORLD.Send(left_send_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			flowField_.SetEtta()[parameters_.get_num_cells(0)+1][i]=right_recv_buffer[i];
		}
	}
		
}

void CommunicationManager::updateFrontNeighbour(){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			front_send_buffer[i]=flowField_.GetEtta()[i][parameters_.get_num_cells(1)];
		}
		MPI::COMM_WORLD.Send(front_send_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			flowField_.SetEtta()[i][0]=back_recv_buffer[i];
		}
	}

}

void CommunicationManager::updateBackNeighbour(){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			back_send_buffer[i]=flowField_.GetEtta()[i][1];
		}
		MPI::COMM_WORLD.Send(back_send_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			flowField_.SetEtta()[i][parameters_.get_num_cells(1)+1]=front_recv_buffer[i];
		}
	}

}
