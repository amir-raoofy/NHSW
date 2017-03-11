#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){}
//CommunicationManager::CommunicationManager(){}
CommunicationManager::~CommunicationManager(){}

