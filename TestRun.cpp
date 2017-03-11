#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

void Simulation::Run(){

	Output output(parameters_, flowField_);
	output.write(0, "./output/");

	InitEtta();
	Initm();
	InitM();
	InitDzI();
	InitDzJ();
	InitDzK();
	InitU();
	InitV();
	InitW();
	InitQ();
	InitGI();
	InitGJ();
	InitGK();
	Updatem();	
	UpdateM();	
	UpdateDzI();
	UpdateDzJ();
	UpdateDzK();
	UpdateGI();
	UpdateGJ();
	UpdateGK();

	CalculateZAZI();
	CalculateZAZJ();
	CalculateZAGI();
	CalculateZAGJ();
	CalculateDelta();
	FirstStepUpdateEtta();
	FirstStepUpdateU();
	FirstStepUpdateV();
	FirstStepUpdateW();
	flowField_.PrintData(1);
  output.write(1, "./output/");

}
