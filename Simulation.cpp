#include "Simulation.h"
#include "defaultScenario.h"

Simulation::Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager)
	{
		time_step=parameters_.get_time_step();
		scenario_ = new defaultScenario(parameters,flowField, communicationManager);
	}

Simulation::~Simulation(){
	delete scenario_;
}

void Simulation::printTimeMeasurements(){
}

