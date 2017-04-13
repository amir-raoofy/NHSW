#include "Simulation.h"

Simulation::Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager)
	{
		time_step=parameters_.get_time_step();
	}

Simulation::~Simulation(){}
