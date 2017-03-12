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

void CommunicationManager::communicteEtta(){

	updateRightNeighbour(flowField_.SetEtta());
	updateLeftNeighbour(flowField_.SetEtta());
	updateFrontNeighbour(flowField_.SetEtta());
	updateBackNeighbour(flowField_.SetEtta());

}

void CommunicationManager::communicteU(){

	updateRightNeighbour(flowField_.SetU());
	updateLeftNeighbour(flowField_.SetU());
	updateFrontNeighbour(flowField_.SetU());
	updateBackNeighbour(flowField_.SetU());

}

void CommunicationManager::communicteV(){

	updateRightNeighbour(flowField_.SetU());
	updateLeftNeighbour(flowField_.SetU());
	updateFrontNeighbour(flowField_.SetU());
	updateBackNeighbour(flowField_.SetU());

}

void CommunicationManager::communicteW(){

	updateRightNeighbour(flowField_.SetU());
	updateLeftNeighbour(flowField_.SetU());
	updateFrontNeighbour(flowField_.SetU());
	updateBackNeighbour(flowField_.SetU());

}

void CommunicationManager::updateRightNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			right_send_buffer[i]=field[parameters_.get_num_cells(0)][i];
		}
		MPI::COMM_WORLD.Send(right_send_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[0][i]=left_recv_buffer[i];
		}
	}

}

void CommunicationManager::updateLeftNeighbour(DiscreteRectangle &field){
		
	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			left_send_buffer[i]=field[1][i];
		}
		MPI::COMM_WORLD.Send(left_send_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[parameters_.get_num_cells(0)+1][i]=right_recv_buffer[i];
		}
	}
						
}

void CommunicationManager::updateFrontNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			front_send_buffer[i]=field[i][parameters_.get_num_cells(1)];
		}
		MPI::COMM_WORLD.Send(front_send_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[i][0]=back_recv_buffer[i];
		}
	}
	
}

void CommunicationManager::updateBackNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			back_send_buffer[i]=field[i][1];
		}
		MPI::COMM_WORLD.Send(back_send_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[i][parameters_.get_num_cells(1)+1]=front_recv_buffer[i];
		}
	}
				
}


void CommunicationManager::updateRightNeighbour(DiscreteCube &field){

}
				
void CommunicationManager::updateLeftNeighbour(DiscreteCube &field){

}

void CommunicationManager::updateFrontNeighbour(DiscreteCube &field){

}

void CommunicationManager::updateBackNeighbour(DiscreteCube &field){

}
