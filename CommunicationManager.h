#pragma once
#include "Parameters.h"
#include "FlowField.h"

class CommunicationManager
{
public:
	CommunicationManager(const Parameters& parameters, FlowField& flowField);
	~CommunicationManager();
	
	void communicteEtta();
	void communicteU();
	void communicteV();
	void communicteW();

private:
	const Parameters& parameters_;
	FlowField& flowField_;

	FLOAT* right_send_buffer;
	FLOAT* left_send_buffer;
	FLOAT* front_send_buffer;
	FLOAT* back_send_buffer;
	FLOAT* right_recv_buffer;
	FLOAT* left_recv_buffer;
	FLOAT* front_recv_buffer;
	FLOAT* back_recv_buffer;

	void updateRightNeighbour(DiscreteRectangle &field);
	void updateLeftNeighbour(DiscreteRectangle &field);
	void updateFrontNeighbour(DiscreteRectangle &field);
	void updateBackNeighbour(DiscreteRectangle &field);

	void updateRightNeighbour(DiscreteCube &field);
	void updateLeftNeighbour(DiscreteCube &field);
	void updateFrontNeighbour(DiscreteCube &field);
	void updateBackNeighbour(DiscreteCube &field);

};
