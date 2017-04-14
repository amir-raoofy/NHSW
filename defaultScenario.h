#include "Scenario.h"

class defaultScenario: public Scenario
{
public:
	defaultScenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	~defaultScenario();

	virtual void InitU();
	virtual void InitV();
	virtual void InitW();
	virtual void InitEtta();

	virtual void Initm();
	virtual void InitM();

	virtual void InitDzI();
	virtual void InitDzJ();
	virtual void InitDzK();
	virtual void InitGI();
	virtual void InitGJ();
	virtual void InitGK();

	virtual void updateBoundariesm();
	virtual void updateBoundariesM();
	virtual void updateBoundariesDzI();
	virtual void updateBoundariesDzJ();
	virtual void updateBoundariesDzK();
	virtual void updateBoundariesGI();
	virtual void updateBoundariesGJ();
	virtual void updateBoundariesGK();
	virtual void updateBoundariesZAZI();
	virtual void updateBoundariesZAZJ();
	virtual void updateBoundariesZAGI();
	virtual void updateBoundariesZAGJ();
	virtual void updateBoundariesDelta();
	virtual void updateBoundariesEtta();
	virtual void updateBoundariesU();
	virtual void updateBoundariesV();
	virtual void updateBoundariesW();

};
