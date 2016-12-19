#include "Simulation.h" 
#include "Solver.h"

// TODO check the implementation of each function -> are the results correct?
//
void Simulation::Run(){
	InitEtta();
//	InitEttaBoundaries();
	Initm();									//DONE TESTED
	InitM();									//DONE TESTED
	InitDzI();								//DONE TESTED
	InitDzJ();								//DONE TESTED
	InitU();									//DONE TESTED
	InitV();									//DONE TESTED
	InitW();									//DONE TESTED
	InitQ();									//DONE TESTED
	InitGI();									//DONE TESTED
	InitGJ();									//DONE TESTED
	//initialization is finished
	//time step
	for (int i = 0; i < 100; i++) {
		Updatem();					//redundant for the very first time step
		UpdateM();					//redundant for the very first time step

		UpdateCellNumberDzI();	//TODO test
		UpdateCellNumberDzJ();	//TODO test
		UpdateCellNumberU();		//TODO test
		UpdateCellNumberV();		//TODO test
		UpdateCellNumberGI();		//TODO test
		UpdateCellNumberGJ();		//TODO test
	
		UpdateDzI();						//TODO test
		UpdateDzJ();						//TODO test
		UpdateGI();							//TODO test
		UpdateGJ();							//TODO test

		CalculateZAZI();
		CalculateZAZJ();
		CalculateZAGI();
		CalculateZAGJ();
		CalculateDelta();
		FirstStepUpdateEtta();
		FirstStepUpdateU();
		FirstStepUpdateV();
	}
}

//TODO make all the solvers members of Simulation
