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

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitU();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitV();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitW();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitQ();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitGI();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitGJ();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "======INITm=======" << std::endl;
	InitGK();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "++++++++++++++++++" << std::endl;
	std::cout << "++++++++++++++++++" << std::endl;
	std::cout << "===INITCOMPLETE===" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====FIRSTLOOP=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "=====UPDATEm=======" << std::endl;
	Updatem();	
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "=====UPDATEM=======" << std::endl;
	UpdateM();	
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZI=====" << std::endl;
	UpdateDzI();
	std::cout << "=====COMPLETE=====" << std::endl;
		
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZJ=====" << std::endl;
	UpdateDzJ();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZK=====" << std::endl;
	UpdateDzK();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZK=====" << std::endl;
	UpdateGI();
	std::cout << "=====COMPLETE=====" << std::endl;

	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZK=====" << std::endl;
	UpdateGJ();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	std::cout << "=====CHECKING=====" << std::endl;
	std::cout << "====UPDATEDZK=====" << std::endl;
	UpdateGK();
	std::cout << "=====COMPLETE=====" << std::endl;
	
	/*	
	//initialization is finished
	//time step
	output.write(0, "./output/");
	for (int i = 0; i < 1 ; i++) {
		
		UpdateCellNumberDzI();		// depricated
		UpdateCellNumberDzJ();		// depricated
		UpdateCellNumberDzK();		// depricated
		UpdateCellNumberU();			// depricated
		UpdateCellNumberV();			// depricated
		UpdateCellNumberW();			// depricated
		UpdateCellNumberQ();			// depricated
		UpdateCellNumberGI();			// depricated
		UpdateCellNumberGJ();			// depricated
		UpdateCellNumberGK();			// depricated
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
