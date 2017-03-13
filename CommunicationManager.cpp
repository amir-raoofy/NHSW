#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){

	right_send_buffer_line 	= new FLOAT [parameters_.get_num_cells(1)+2];
	left_send_buffer_line 	= new FLOAT [parameters_.get_num_cells(1)+2];
	front_send_buffer_line 	= new FLOAT [parameters_.get_num_cells(0)+2];
	back_send_buffer_line 	= new FLOAT [parameters_.get_num_cells(0)+2];
	right_recv_buffer_line 	= new FLOAT [parameters_.get_num_cells(1)+2];
	left_recv_buffer_line 	= new FLOAT [parameters_.get_num_cells(1)+2];
	front_recv_buffer_line 	= new FLOAT [parameters_.get_num_cells(0)+2];
	back_recv_buffer_line 	= new FLOAT [parameters_.get_num_cells(0)+2];

	right_send_buffer_rectangle  = new FLOAT [(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2)];
	left_send_buffer_rectangle   = new FLOAT [(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2)];
	front_send_buffer_rectangle  = new FLOAT [(parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2)];
	back_send_buffer_rectangle   = new FLOAT [(parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2)];
	right_recv_buffer_rectangle  = new FLOAT [(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2)];
	left_recv_buffer_rectangle   = new FLOAT [(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2)];
	front_recv_buffer_rectangle  = new FLOAT [(parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2)];
	back_recv_buffer_rectangle   = new FLOAT [(parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2)];

}

CommunicationManager::~CommunicationManager(){

	delete [] right_send_buffer_line;
	delete [] left_send_buffer_line;
	delete [] front_send_buffer_line;
	delete [] back_send_buffer_line;
	delete [] right_recv_buffer_line;
	delete [] left_recv_buffer_line;
	delete [] front_recv_buffer_line;
	delete [] back_recv_buffer_line;

	delete [] right_send_buffer_rectangle;
	delete [] left_send_buffer_rectangle;
	delete [] front_send_buffer_rectangle;
	delete [] back_send_buffer_rectangle;
	delete [] right_recv_buffer_rectangle;
	delete [] left_recv_buffer_rectangle;
	delete [] front_recv_buffer_rectangle;
	delete [] back_recv_buffer_rectangle;

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

	updateRightNeighbour(flowField_.SetV());
	updateLeftNeighbour(flowField_.SetV());
	updateFrontNeighbour(flowField_.SetV());
	updateBackNeighbour(flowField_.SetV());

}

void CommunicationManager::communicteW(){

	updateRightNeighbour(flowField_.SetW());
	updateLeftNeighbour(flowField_.SetW());
	updateFrontNeighbour(flowField_.SetW());
	updateBackNeighbour(flowField_.SetW());

}

void CommunicationManager::communicteDzI(){

	updateRightNeighbour(flowField_.SetDzI());
	updateLeftNeighbour(flowField_.SetDzI());
	updateFrontNeighbour(flowField_.SetDzI());
	updateBackNeighbour(flowField_.SetDzI());

}

void CommunicationManager::communicteDzJ(){

	updateRightNeighbour(flowField_.SetDzJ());
	updateLeftNeighbour(flowField_.SetDzJ());
	updateFrontNeighbour(flowField_.SetDzJ());
	updateBackNeighbour(flowField_.SetDzJ());

}

void CommunicationManager::communicteDzK(){

	updateRightNeighbour(flowField_.SetDzK());
	updateLeftNeighbour(flowField_.SetDzK());
	updateFrontNeighbour(flowField_.SetDzK());
	updateBackNeighbour(flowField_.SetDzK());

}

void CommunicationManager::communicteGI(){

	updateRightNeighbour(flowField_.SetGI());
	updateLeftNeighbour(flowField_.SetGI());
	updateFrontNeighbour(flowField_.SetGI());
	updateBackNeighbour(flowField_.SetGI());

}

void CommunicationManager::communicteGJ(){

	updateRightNeighbour(flowField_.SetGJ());
	updateLeftNeighbour(flowField_.SetGJ());
	updateFrontNeighbour(flowField_.SetGJ());
	updateBackNeighbour(flowField_.SetGJ());

}

void CommunicationManager::communicteGK(){

	updateRightNeighbour(flowField_.SetGK());
	updateLeftNeighbour(flowField_.SetGK());
	updateFrontNeighbour(flowField_.SetGK());
	updateBackNeighbour(flowField_.SetGK());

}

void CommunicationManager::updateRightNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			right_send_buffer_line[i]=field[parameters_.get_num_cells(0)][i];
		}
		MPI::COMM_WORLD.Send(right_send_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[0][i]=left_recv_buffer_line[i];
		}
	}

}

void CommunicationManager::updateLeftNeighbour(DiscreteRectangle &field){
		
	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			left_send_buffer_line[i]=field[1][i];
		}
		MPI::COMM_WORLD.Send(left_send_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[parameters_.get_num_cells(0)+1][i]=right_recv_buffer_line[i];
		}
	}
						
}

void CommunicationManager::updateFrontNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			front_send_buffer_line[i]=field[i][parameters_.get_num_cells(1)];
		}
		MPI::COMM_WORLD.Send(front_send_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[i][0]=back_recv_buffer_line[i];
		}
	}
	
}

void CommunicationManager::updateBackNeighbour(DiscreteRectangle &field){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			back_send_buffer_line[i]=field[i][1];
		}
		MPI::COMM_WORLD.Send(back_send_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[i][parameters_.get_num_cells(1)+1]=front_recv_buffer_line[i];
		}
	}
				
}


void CommunicationManager::updateRightNeighbour(DiscreteCube &field){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				right_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[parameters_.get_num_cells(0)][i][k];
			}
		}
		MPI::COMM_WORLD.Send(right_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[0][i][k]=left_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

}
				
void CommunicationManager::updateLeftNeighbour(DiscreteCube &field){
	
	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				left_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[1][i][k];
			}
		}
		MPI::COMM_WORLD.Send(left_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[parameters_.get_num_cells(0)+1][i][k]=right_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

}

void CommunicationManager::updateFrontNeighbour(DiscreteCube &field){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				front_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[i][parameters_.get_num_cells(1)][k];
			}
		}
		MPI::COMM_WORLD.Send(front_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[i][0][k]=back_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

}

void CommunicationManager::updateBackNeighbour(DiscreteCube &field){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				back_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[i][1][k];
			}
		}
		MPI::COMM_WORLD.Send(back_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[i][parameters_.get_num_cells(1)+1][k]=front_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

}
