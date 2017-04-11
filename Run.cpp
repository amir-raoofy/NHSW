#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

// TODO check the implementation of each function -> are the results correct?
//
void Simulation::Run(){

	Output output(parameters_, flowField_);
	InitEtta();
	Initm();									//DONE TESTED
	InitM();									//DONE TESTED
	InitDzI();								//DONE TESTED
	InitDzJ();								//DONE TESTED
	InitDzK();								//TODO test
	InitU();									//DONE TESTED
	InitV();									//DONE TESTED
	InitW();									//DONE TESTED
	InitGI();									//DONE TESTED
	InitGJ();									//DONE TESTED
	InitGK();									//TODO test
	//initialization is finished
	//time step
	output.write(0, "./output/");
	
	for (int i = 0; i < 100; i++) {
		std::cout << "here" << std::endl;
		Updatem();					//redundant for the very first time step
		UpdateM();					//redundant for the very first time step
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
		flowField_.PrintDelta();
		UpdateEtta();
		UpdateU();
		UpdateV();
		UpdateW();		//TODO test

		output.write(i+1, "./output/");
	}
}
