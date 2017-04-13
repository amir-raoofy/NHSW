#include "Simulation.h"

void Simulation::UpdateSimulationTimeStep(){
	//parameters_.set_time_step(time_step);
	//parameters_.set_time_step(0.01);
	MPI_Barrier(parameters_.topology.communicator);
	time_step=parameters_.get_time_step();
	std::cout << "time step" << time_step << std::endl;
	MPI_Barrier(parameters_.topology.communicator);
}
