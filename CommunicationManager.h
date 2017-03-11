#pragma once
#include "Parameters.h"
#include "FlowField.h"

class CommunicationManager
{
public:
	CommunicationManager(const Parameters& parameters, FlowField& flowField);
	//CommunicationManager();
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

};
