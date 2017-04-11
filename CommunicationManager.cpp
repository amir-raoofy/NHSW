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

	updateRightNeighbour2d(flowField_.etta);
	updateLeftNeighbour2d(flowField_.etta);
	updateFrontNeighbour2d(flowField_.etta);
	updateBackNeighbour2d(flowField_.etta);

}

void CommunicationManager::communicteU(){

	updateRightNeighbour3d(flowField_.u);
	updateLeftNeighbour3d(flowField_.u);
	updateFrontNeighbour3d(flowField_.u);
	updateBackNeighbour3d(flowField_.u);

}

void CommunicationManager::communicteV(){

	updateRightNeighbour3d(flowField_.v);
	updateLeftNeighbour3d(flowField_.v);
	updateFrontNeighbour3d(flowField_.v);
	updateBackNeighbour3d(flowField_.v);

}

void CommunicationManager::communicteW(){

	updateRightNeighbour3d(flowField_.w);
	updateLeftNeighbour3d(flowField_.w);
	updateFrontNeighbour3d(flowField_.w);
	updateBackNeighbour3d(flowField_.w);

}

void CommunicationManager::communicteDzI(){

	updateRightNeighbour3d(flowField_.dz_i);
	updateLeftNeighbour3d(flowField_.dz_i);
	updateFrontNeighbour3d(flowField_.dz_i);
	updateBackNeighbour3d(flowField_.dz_i);

}

void CommunicationManager::communicteDzJ(){

	updateRightNeighbour3d(flowField_.dz_j);
	updateLeftNeighbour3d(flowField_.dz_j);
	updateFrontNeighbour3d(flowField_.dz_j);
	updateBackNeighbour3d(flowField_.dz_j);

}

void CommunicationManager::communicteDzK(){

	updateRightNeighbour3d(flowField_.dz_k);
	updateLeftNeighbour3d(flowField_.dz_k);
	updateFrontNeighbour3d(flowField_.dz_k);
	updateBackNeighbour3d(flowField_.dz_k);

}

void CommunicationManager::communicteGI(){

	updateRightNeighbour3d(flowField_.g_i);
	updateLeftNeighbour3d(flowField_.g_i);
	updateFrontNeighbour3d(flowField_.g_i);
	updateBackNeighbour3d(flowField_.g_i);

}

void CommunicationManager::communicteGJ(){

	updateRightNeighbour3d(flowField_.g_j);
	updateLeftNeighbour3d(flowField_.g_j);
	updateFrontNeighbour3d(flowField_.g_j);
	updateBackNeighbour3d(flowField_.g_j);

}

void CommunicationManager::communicteGK(){

	updateRightNeighbour3d(flowField_.g_k);
	updateLeftNeighbour3d(flowField_.g_k);
	updateFrontNeighbour3d(flowField_.g_k);
	updateBackNeighbour3d(flowField_.g_k);

}

void CommunicationManager::communicteZazi(){
		
	updateRightNeighbour2d(flowField_.zaz_i);
	updateLeftNeighbour2d(flowField_.zaz_i);
	updateFrontNeighbour2d(flowField_.zaz_i);
	updateBackNeighbour2d(flowField_.zaz_i);

}

void CommunicationManager::communicteZazj(){

	updateRightNeighbour2d(flowField_.zaz_j);
	updateLeftNeighbour2d(flowField_.zaz_j);
	updateFrontNeighbour2d(flowField_.zaz_j);
	updateBackNeighbour2d(flowField_.zaz_j);

}

void CommunicationManager::communicteZagi(){

	updateRightNeighbour2d(flowField_.zag_i);
	updateLeftNeighbour2d(flowField_.zag_i);
	updateFrontNeighbour2d(flowField_.zag_i);
	updateBackNeighbour2d(flowField_.zag_i);

}

void CommunicationManager::communicteZagj(){

	updateRightNeighbour2d(flowField_.zag_j);
	updateLeftNeighbour2d(flowField_.zag_j);
	updateFrontNeighbour2d(flowField_.zag_j);
	updateBackNeighbour2d(flowField_.zag_j);

}

void CommunicationManager::communicteDelta(){

	updateRightNeighbour2d(flowField_.delta);
	updateLeftNeighbour2d(flowField_.delta);
	updateFrontNeighbour2d(flowField_.delta);
	updateBackNeighbour2d(flowField_.delta);

}

void CommunicationManager::updateRightNeighbour2d(FLOAT* field){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			right_send_buffer_line[i]=field[map(parameters_.get_num_cells(0),i)];
		}
		MPI::COMM_WORLD.Send(right_send_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[map(0,i)]=left_recv_buffer_line[i];
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}

void CommunicationManager::updateLeftNeighbour2d(FLOAT* field){
		
	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			left_send_buffer_line[i]=field[map(1,i)];
		}
		MPI::COMM_WORLD.Send(left_send_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer_line, parameters_.get_num_cells(1)+2, MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			field[map(parameters_.get_num_cells(0)+1,i)]=right_recv_buffer_line[i];
		}
	}
						
	MPI_Barrier(parameters_.topology.communicator);

}

void CommunicationManager::updateFrontNeighbour2d(FLOAT* field){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			front_send_buffer_line[i]=field[map(i,parameters_.get_num_cells(1))];
		}
		MPI::COMM_WORLD.Send(front_send_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[map(i,0)]=back_recv_buffer_line[i];
		}
	}
	
	MPI_Barrier(parameters_.topology.communicator);

}

void CommunicationManager::updateBackNeighbour2d(FLOAT* field){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			back_send_buffer_line[i]=field[map(i,1)];
		}
		MPI::COMM_WORLD.Send(back_send_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer_line, parameters_.get_num_cells(0)+2, MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			field[map(i,parameters_.get_num_cells(1)+1)]=front_recv_buffer_line[i];
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}


void CommunicationManager::updateRightNeighbour3d(FLOAT* field){

	if (parameters_.topology.right_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				right_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[map(parameters_.get_num_cells(0),i,k)];
			}
		}
		MPI::COMM_WORLD.Send(right_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.right_id, 0);
	}

	if (parameters_.topology.left_id!=-1) {
		MPI::COMM_WORLD.Recv(left_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.left_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[map(0,i,k)]=left_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}
				
void CommunicationManager::updateLeftNeighbour3d(FLOAT* field){
	
	if (parameters_.topology.left_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				left_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[map(1,i,k)];
			}
		}
		MPI::COMM_WORLD.Send(left_send_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.left_id, 0);
	}

	if (parameters_.topology.right_id!=-1) {
		MPI::COMM_WORLD.Recv(right_recv_buffer_rectangle, (parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.right_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(1)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[map(parameters_.get_num_cells(0)+1,i,k)]=right_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}

void CommunicationManager::updateFrontNeighbour3d(FLOAT* field){

	if (parameters_.topology.front_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				front_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[map(i,parameters_.get_num_cells(1),k)];
			}
		}
		MPI::COMM_WORLD.Send(front_send_buffer_rectangle, (parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.front_id, 0);
	}

	if (parameters_.topology.back_id!=-1) {
		MPI::COMM_WORLD.Recv(back_recv_buffer_rectangle, (parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.back_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[map(i,0,k)]=back_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}

void CommunicationManager::updateBackNeighbour3d(FLOAT* field){

	if (parameters_.topology.back_id!=-1)  {
		//fill the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				back_send_buffer_rectangle[i*parameters_.get_num_cells(2)+k]=field[map(i,1,k)];
			}
		}
		MPI::COMM_WORLD.Send(back_send_buffer_rectangle, (parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.back_id, 0);
	}

	if (parameters_.topology.front_id!=-1) {
		MPI::COMM_WORLD.Recv(front_recv_buffer_rectangle, (parameters_.get_num_cells(0)+2)*parameters_.get_num_cells(2), MPI::DOUBLE, parameters_.topology.front_id, 0);
		//read the buffer
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[map(i,parameters_.get_num_cells(1)+1,k)]=front_recv_buffer_rectangle[i*parameters_.get_num_cells(2)+k];
			}
		}
	}

	MPI_Barrier(parameters_.topology.communicator);

}


