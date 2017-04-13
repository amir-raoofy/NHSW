#include "Simulation.h"
#include <algorithm>

void Simulation::UpdateSimulationTimeStep(){
	
	FLOAT maxU_send,minU_send,maxV_send,minV_send,maxW_send,minW_send;
	FLOAT maxU_recv,minU_recv,maxV_recv,minV_recv,maxW_recv,minW_recv;	
	
	MPI_Barrier(parameters_.topology.communicator);
	int LENGTH = (parameters_.get_num_cells(0)+2) * (parameters_.get_num_cells(1)+2) * parameters_.get_num_cells(2);
	maxU_send = *std::max_element(flowField_.u, flowField_.u + LENGTH);
	minU_send = *std::min_element(flowField_.u, flowField_.u + LENGTH);

	maxV_send = *std::max_element(flowField_.v, flowField_.v + LENGTH);
	minV_send = *std::min_element(flowField_.v, flowField_.v + LENGTH);

	maxW_send = *std::max_element(flowField_.w, flowField_.w + LENGTH);
	minW_send = *std::min_element(flowField_.w, flowField_.w + LENGTH);

	MPI::COMM_WORLD.Allreduce(&maxU_send, &maxU_recv, 1, MPI_DOUBLE, MPI_MAX);
	MPI::COMM_WORLD.Allreduce(&minU_send, &minU_recv, 1, MPI_DOUBLE, MPI_MIN);
	MPI::COMM_WORLD.Allreduce(&maxV_send, &maxV_recv, 1, MPI_DOUBLE, MPI_MAX);
	MPI::COMM_WORLD.Allreduce(&minV_send, &minV_recv, 1, MPI_DOUBLE, MPI_MIN);
	MPI::COMM_WORLD.Allreduce(&maxW_send, &maxW_recv, 1, MPI_DOUBLE, MPI_MAX);
	MPI::COMM_WORLD.Allreduce(&minW_send, &minW_recv, 1, MPI_DOUBLE, MPI_MIN);

	time_step=std::min(	parameters_.get_tau()/
	(std::max(std::abs(maxU_recv),std::abs(minU_recv))/parameters_.get_dxdydz(0)+
	std::max(std::abs(maxV_recv),std::abs(minV_recv))/parameters_.get_dxdydz(1)+
	std::max(std::abs(maxW_recv),std::abs(minW_recv))/parameters_.get_dxdydz(2)+
	(2*1000*parameters_.get_viscosity())*( 1/(parameters_.get_dxdydz(0)*parameters_.get_dxdydz(0))+
	1/(parameters_.get_dxdydz(1)*parameters_.get_dxdydz(1))) ) ,parameters_.get_time_step());

	MPI_Barrier(parameters_.topology.communicator);

}
