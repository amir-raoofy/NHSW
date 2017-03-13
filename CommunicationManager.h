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
	void communicteDzI();
	void communicteDzJ();
	void communicteDzK();
	void communicteGI();
	void communicteGJ();
	void communicteGK();

private:
	const Parameters& parameters_;
	FlowField& flowField_;

	FLOAT* right_send_buffer_line;
	FLOAT* left_send_buffer_line;
	FLOAT* front_send_buffer_line;
	FLOAT* back_send_buffer_line;
	FLOAT* right_recv_buffer_line;
	FLOAT* left_recv_buffer_line;
	FLOAT* front_recv_buffer_line;
	FLOAT* back_recv_buffer_line;

	FLOAT* right_send_buffer_rectangle;
	FLOAT* left_send_buffer_rectangle;
	FLOAT* front_send_buffer_rectangle;
	FLOAT* back_send_buffer_rectangle;
	FLOAT* right_recv_buffer_rectangle;
	FLOAT* left_recv_buffer_rectangle;
	FLOAT* front_recv_buffer_rectangle;
	FLOAT* back_recv_buffer_rectangle;

	void updateRightNeighbour(DiscreteRectangle &field);
	void updateLeftNeighbour(DiscreteRectangle &field);
	void updateFrontNeighbour(DiscreteRectangle &field);
	void updateBackNeighbour(DiscreteRectangle &field);

	void updateRightNeighbour(DiscreteCube &field);
	void updateLeftNeighbour(DiscreteCube &field);
	void updateFrontNeighbour(DiscreteCube &field);
	void updateBackNeighbour(DiscreteCube &field);

};
