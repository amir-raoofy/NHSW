#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

void Simulation::Run(){

	Output output(parameters_, flowField_);

	InitEtta();
	communicationManager_.communicteEtta();
	MPI_Barrier(parameters_.topology.communicator);
	Initm();
	InitM();
	InitDzI();
	communicationManager_.communicteDzI();
	MPI_Barrier(parameters_.topology.communicator);
	

	InitDzJ();
	communicationManager_.communicteDzJ();
	MPI_Barrier(parameters_.topology.communicator);
	InitDzK();
	communicationManager_.communicteDzK();
	MPI_Barrier(parameters_.topology.communicator);
	InitU();
	communicationManager_.communicteU();
	MPI_Barrier(parameters_.topology.communicator);
	InitV();
	communicationManager_.communicteV();
	MPI_Barrier(parameters_.topology.communicator);
	InitW();
	communicationManager_.communicteW();
	MPI_Barrier(parameters_.topology.communicator);
	InitQ();
	InitGI();
	communicationManager_.communicteGI();
	MPI_Barrier(parameters_.topology.communicator);
	InitGJ();
	communicationManager_.communicteGJ();
	MPI_Barrier(parameters_.topology.communicator);
	InitGK();
	communicationManager_.communicteGK();
	MPI_Barrier(parameters_.topology.communicator);

	output.write(0, "./output/");
	for (int i = 1; i < 2; i++) {
		Updatem();	
		UpdateM();	
		UpdateDzI();
		communicationManager_.communicteDzI();
		MPI_Barrier(parameters_.topology.communicator);
		UpdateDzJ();
		communicationManager_.communicteDzJ();
		MPI_Barrier(parameters_.topology.communicator);
		UpdateDzK();
		communicationManager_.communicteDzK();
		MPI_Barrier(parameters_.topology.communicator);
		UpdateGI();
		communicationManager_.communicteGI();
		MPI_Barrier(parameters_.topology.communicator);
		UpdateGJ();
		communicationManager_.communicteGJ();
		MPI_Barrier(parameters_.topology.communicator);
		UpdateGK();
		communicationManager_.communicteGK();
		MPI_Barrier(parameters_.topology.communicator);
	
		CalculateZAZI();
		CalculateZAZJ();
		CalculateZAGI();
		CalculateZAGJ();
		CalculateDelta();
		FirstStepUpdateEtta();
		communicationManager_.communicteEtta();
		MPI_Barrier(parameters_.topology.communicator);
		FirstStepUpdateU();
		communicationManager_.communicteU();
		MPI_Barrier(parameters_.topology.communicator);
		FirstStepUpdateV();
		communicationManager_.communicteV();
		MPI_Barrier(parameters_.topology.communicator);
		FirstStepUpdateW();
		communicationManager_.communicteV();
		MPI_Barrier(parameters_.topology.communicator);
		output.write(i, "./output/");
		
	}
	


	//parameters_.topology.print();
	
	MPI_Barrier(parameters_.topology.communicator);
	for (int i = 0; i < parameters_.topology.np; i++) {
			MPI_Barrier(parameters_.topology.communicator);
			if (parameters_.topology.id == i)	
				flowField_.printEtta(1);
	}
	MPI_Barrier(parameters_.topology.communicator);

/*
	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i) {
						std::cout << "rank: " << i << std::endl;
		}
*/
}
