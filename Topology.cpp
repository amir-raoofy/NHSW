#include "Topology.h"
#include <math.h>
#include <iostream>

Topology::Topology(int argc, char *argv[]){

	MPI::Init(argc, argv);
	np  = MPI::COMM_WORLD.Get_size();
	id = MPI::COMM_WORLD.Get_rank();

	int dim[2];
	bool period[2];
	int reorder = 0;
	period[0]=0; period[1]=0;

	set_nx_ny();
	dim[0]=npx; dim[1]=npy;
	communicator=MPI::COMM_WORLD.Create_cart(2,dim,period,reorder);
	set_neighbour_ids();
}

Topology::Topology(){

	MPI::Init();
	np  = MPI::COMM_WORLD.Get_size();
	id = MPI::COMM_WORLD.Get_rank();

	int dim[2];
	bool period[2];
	int reorder = 0;
	period[0]=0; period[1]=0;

	set_nx_ny();
	dim[0]=npx; dim[1]=npy;
	communicator=MPI::COMM_WORLD.Create_cart(2,dim,period,reorder);
	set_neighbour_ids();
}

Topology::~Topology(){

	MPI::Finalize();	

}

void Topology::set_nx_ny(){
	npy=floor(sqrt(np));
	while (npy>0) {
		if (np%npy==0) {
			break;
		}
		npy--;
	}
	npx=np/npy;
}

void Topology::set_neighbour_ids(){
	
	int coords[2];
	MPI_Cart_coords(communicator,id,2,coords);
	
	id_x=coords[0];
	id_y=coords[1];

	coords[0]--;
	if (coords[0]==-1) {
		left_id = -1;
	}
	else{
		MPI_Cart_rank(communicator, coords, &left_id);
	}

	coords[0]++;
	coords[0]++;
	if (coords[0]==npx) {
		right_id = -1;
	}
	else{
		MPI_Cart_rank(communicator, coords, &right_id);
	}
	coords[0]--;

	coords[1]--;
	if (coords[1]==-1) {
		back_id = -1;
	}
	else{
		MPI_Cart_rank(communicator, coords, &back_id);
	}

	coords[1]++;
	coords[1]++;
	if (coords[1]==npy) {
		front_id = -1;
	}
	else{
		MPI_Cart_rank(communicator, coords, &front_id);
	}
	coords[1]--;

}

void Topology::print(){

	if (id == 0) {
		std::cout << "nx: " << npx << " ny: " << npy << std::endl;
	}

	std::cout << "my rank is: " << id <<  ", l: " << left_id << ", r:" << right_id << ", b:" << back_id << ", f:" << front_id << std::endl;
	
}
