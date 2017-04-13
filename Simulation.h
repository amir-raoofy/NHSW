#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"

class Simulation
{
public:

	Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	~Simulation();

	void InitU();
	void InitV();
	void InitW();
	void InitEtta();

	void Initm();
	void InitM();

	void InitDzI();
	void InitDzJ();
	void InitDzK();
	void InitGI();
	void InitGJ();
	void InitGK();
	void InitDelta();	
	void InitZAZI();
	void InitZAZJ();
	void InitZAGI();
	void InitZAGJ();

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
	CommunicationManager& communicationManager_;
	FLOAT time_step;

};
