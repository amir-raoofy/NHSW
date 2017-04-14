#include "Parameters.h"
#include "FlowField.h"
#include "Scenario.h"
#include "CommunicationManager.h"

class Simulation
{
public:

	Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	~Simulation();

	void UpdateU();
	void UpdateV();
	void UpdateW();
	void UpdateEtta();
	void ParallelUpdateEtta();
	
	void Updatem();
	void UpdateM();
	
	void UpdateDzI();
	void UpdateDzJ();
	void UpdateDzK();
	void UpdateGI();
	void UpdateGJ();
	void UpdateGK();
	void CalculateDelta();	
	void CalculateZAZI();
	void CalculateZAZJ();
	void CalculateZAGI();
	void CalculateZAGJ();

	void UpdateSimulationTimeStep();

	void Run();

	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}

private:
	const Parameters& parameters_;
	FlowField& flowField_;
	Scenario* scenario_;
	CommunicationManager& communicationManager_;
	FLOAT time_step;

};
