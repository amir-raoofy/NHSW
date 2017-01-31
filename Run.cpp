#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

// TODO check the implementation of each function -> are the results correct?
//
void Simulation::Run(){

	Output output(parameters_, flowField_);
			
	InitEtta();
//	InitEttaBoundaries();
	Initm();									//DONE TESTED
	InitM();									//DONE TESTED
	InitDzI();								//DONE TESTED
	InitDzJ();								//DONE TESTED
	InitDzK();								//TODO test
	InitU();									//DONE TESTED
	InitV();									//DONE TESTED
	InitW();									//DONE TESTED
	InitQ();									//DONE TESTED
	InitGI();									//DONE TESTED
	InitGJ();									//DONE TESTED
	InitGK();									//TODO test
	//initialization is finished
	//time step
	output.write(0, "./output/");
	for (int i = 0; i < 1000; i++) {
		Updatem();					//redundant for the very first time step
		UpdateM();					//redundant for the very first time step

		UpdateCellNumberDzI();	//TODO test
		UpdateCellNumberDzJ();	//TODO test
		UpdateCellNumberDzK();	//TODO test
		UpdateCellNumberU();		//TODO test
		UpdateCellNumberV();		//TODO test
		UpdateCellNumberW();		//TODO test
		UpdateCellNumberQ();		//TODO test
		UpdateCellNumberGI();		//TODO test
		UpdateCellNumberGJ();		//TODO test
		UpdateCellNumberGK();		//TODO test
		UpdateDzI();						//TODO test
		UpdateDzJ();						//TODO test
		UpdateDzK();						//TODO test
		UpdateGI();							//TODO test
		UpdateGJ();							//TODO test
		UpdateGK();							//TODO test

		CalculateZAZI();
		CalculateZAZJ();
		CalculateZAGI();
		CalculateZAGJ();
		CalculateDelta();
		FirstStepUpdateEtta();
		FirstStepUpdateU();
		FirstStepUpdateV();
		FirstStepUpdateW();		//TODO test
		output.write(i+1, "./output/");

		//TODO check and take care of the boundary conditions more carefully specially at top and bottom and especially for the pressure equation 
		//for which the BC should be replaced by neuman.
		//SolveQ();								//TODO check
		//SecondStepUpdateU();		//TODO check
		//SecondStepUpdateV();		//TODO check
		//SecondStepUpdateW();		//TODO check
		//SecondStepUpdateEtta();	//TODO check

	}
}

//TODO make all the solvers members of Simulation
