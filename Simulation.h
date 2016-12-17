#include "Parameters.h"
#include "FlowField.h"

class Simulation
{
public:
	Simulation(const Parameters& parameters, FlowField& flowField);
	~Simulation();

	// methods
	void InitEtta();
	void InitEttaBoundaries();
	void Initm();
	void InitM();
	void InitU();
	void InitV();
	void InitW();
	void InitQ();
	void InitDzI();
	void InitDzJ();
	void CalculateZAZI();
	void CalculateZAZJ();
	void InitGI();
	void InitGJ();
	void CalculateDelta();	
	void CalculateZAGI();
	void CalculateZAGJ();		//TODO check the congergence of the solver

	void Updatem();
	void UpdateM();
	void UpdateDzI();
	void UpdateDzJ();
	void UpdateGI();
	void UpdateGJ();
	void FirstStepUpdateEtta();
	void FirstStepUpdateU();
	void FirstStepUpdateV();
	void Run();
private:
	const Parameters& parameters_;
	FlowField& flowField_;
	/* data */
};
