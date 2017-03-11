#include "Simulation.h"

Simulation::Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager)
	//communicationManager_(parameters,flowField)
	{}

Simulation::~Simulation(){}
