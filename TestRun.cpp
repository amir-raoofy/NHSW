#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

void Simulation::Run(){

	Output output(parameters_, flowField_);
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "=====INITETTA=====" << std::endl;
	InitEtta();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	Initm();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitM();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitDzI();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitDzJ();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitDzK();
	std::cout << "=====COMPLETE=====" << std::endl;

	/*	
	InitU();
	InitV();
	InitW();
	InitQ();
	InitGI();
	InitGJ();
	InitGK();
	//initialization is finished
	//time step
	output.write(0, "./output/");
	for (int i = 0; i < 1 ; i++) {
		Updatem();					//redundant for the very first time step
		UpdateM();					//redundant for the very first time step

		UpdateCellNumberDzI();
		UpdateCellNumberDzJ();
		UpdateCellNumberDzK();
		UpdateCellNumberU();
		UpdateCellNumberV();
		UpdateCellNumberW();
		UpdateCellNumberQ();
		UpdateCellNumberGI();
		UpdateCellNumberGJ();
		UpdateCellNumberGK();
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
		output.write(i+1, "./output/");
	}
	*/

}
