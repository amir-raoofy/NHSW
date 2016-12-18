#include "Simulation.h" 
#include "Solver.h"

// TODO check the implementation of each function -> are the results correct?
//
void Simulation::Run(){
	InitEtta();
//	InitEttaBoundaries();
	Initm();
	InitM();
	InitDzI();
	InitDzJ();
	InitU();
	InitV();
	InitW();
	InitQ();
	InitGI();
	InitGJ();
	//initialization is finished
	//first time step
	Updatem();					//redundant for the very first time step
	UpdateM();					//redundant for the very first time step

	UpdateCellNumberDzI();
	UpdateCellNumberDzJ();
	UpdateCellNumberU();
	UpdateCellNumberV();
	UpdateCellNumberGI();
	UpdateCellNumberGJ();
	
	UpdateDzI();
	UpdateDzJ();
	UpdateGI();
	UpdateGJ();

	CalculateZAZI();
	CalculateZAZJ();
	CalculateZAGI();
	CalculateZAGJ();
	CalculateDelta();
	FirstStepUpdateEtta();
	FirstStepUpdateU();
	FirstStepUpdateV();
}

//TODO make all the solvers members of Simulation
