#pragma once
#include "Parameters.h"
#include "FlowField.h"

class CommunicationManager
{
public:
	CommunicationManager(const Parameters& parameters, FlowField& flowField);
	~CommunicationManager();
	void updateRightNeighbour();
	void updateLeftNeighbour();
	void updateFrontNeighbour();
	void updateBackNeighbour();

private:
	const Parameters& parameters_;
	FlowField& flowField_;

	int send_buffer;
	int recv_buffer;

	FLOAT* right_send_buffer;
	FLOAT* left_send_buffer;
	FLOAT* front_send_buffer;
	FLOAT* back_send_buffer;
	FLOAT* right_recv_buffer;
	FLOAT* left_recv_buffer;
	FLOAT* front_recv_buffer;
	FLOAT* back_recv_buffer;

};
