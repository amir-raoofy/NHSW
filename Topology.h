#pragma once
#include <mpi.h>

class Topology
{
public:
	Topology(int argc, char *argv[]);
	Topology();
	~Topology();
	void print();	

	int np, npx, npy, id, id_x, id_y, left_id, right_id, front_id, back_id;
	MPI_Comm communicator;

private:
	void set_nx_ny();
	void set_neighbour_ids();
};
