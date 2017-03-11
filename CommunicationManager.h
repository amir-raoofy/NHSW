#pragma once
#include "Parameters.h"
#include "FlowField.h"

class CommunicationManager
{
public:
	CommunicationManager(const Parameters& parameters, FlowField& flowField);
	//CommunicationManager();
	~CommunicationManager();

private:
	const Parameters& parameters_;
	FlowField& flowField_;
};
