#include "Scenario.h"

Scenario::Scenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager){}

Scenario::~Scenario(){}

void Scenario::Init(){

	InitEtta();
	communicationManager_.communicteEtta();
	Initm();
	InitM();
	InitDzI();
	communicationManager_.communicteDzI();
	InitDzJ();
	communicationManager_.communicteDzJ();
	InitDzK();
	communicationManager_.communicteDzK();
	InitU();
	communicationManager_.communicteU();
	InitV();
	communicationManager_.communicteV();
	InitW();
	communicationManager_.communicteW();
	InitGI();
	communicationManager_.communicteGI();
	InitGJ();
	communicationManager_.communicteGJ();
	InitGK();
	communicationManager_.communicteGK();

}
