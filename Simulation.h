#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"

class Simulation
{
public:
	Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
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
	void InitGK();
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
	void UpdateCellNumberGK();
	void UpdateCellNumberU();
	void UpdateCellNumberV();
	void UpdateCellNumberW();
	void UpdateCellNumberQ();

	void UpdateDzI();
	void UpdateDzJ();
	void UpdateDzK();
	void UpdateGI();
	void UpdateGJ();
	void UpdateGK();
	void FirstStepUpdateEtta();
	void ParallelFirstStepUpdateEtta();
	//void PetscFirstStepUpdateEtta();
	void FirstStepUpdateU();
	void FirstStepUpdateV();
	void FirstStepUpdateW();		//TODO implement
	void Run();

	void SolveQ();								//TODO implement
	void SecondStepUpdateU();			//TODO implement
	void SecondStepUpdateV();			//TODO implement
	void SecondStepUpdateW();			//TODO implement
	void SecondStepUpdateEtta();	//TODO implement

private:
	const Parameters& parameters_;
	FlowField& flowField_;
	CommunicationManager& communicationManager_;
	/* data */
};
