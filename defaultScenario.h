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

};
