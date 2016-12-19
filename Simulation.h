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
	void InitDzK();
	void CalculateZAZI();
	void CalculateZAZJ();
	void InitGI();
	void InitGJ();
	void CalculateDelta();	
	void CalculateZAGI();
	void CalculateZAGJ();

	void Updatem();
	void UpdateM();
	void UpdateCellNumberDzI();
	void UpdateCellNumberDzJ();
	void UpdateCellNumberDzK();
	void UpdateCellNumberGI();
	void UpdateCellNumberGJ();
	void UpdateCellNumberU();
	void UpdateCellNumberV();

	void UpdateDzI();
	void UpdateDzJ();
	void UpdateDzK();
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
