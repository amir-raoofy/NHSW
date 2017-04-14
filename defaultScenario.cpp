#include "defaultScenario.h"

defaultScenario::defaultScenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	Scenario(parameters, flowField, communicationManager){}

defaultScenario::~defaultScenario(){}
