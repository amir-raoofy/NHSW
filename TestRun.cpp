#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

void Simulation::Run(){

	Output output(parameters_, flowField_);

	InitEtta();
	communicationManager_.communicteEtta();
	Initm();
	InitM();
	InitDzI();
	communicationManager_.communicteDzI();
	InitDzJ();
	communicationManager_.communicteDzJ();
	InitDzK();
	communicationManager_.communicteDzK();
	InitU();
	communicationManager_.communicteU();
	InitV();
	communicationManager_.communicteV();
	InitW();
	communicationManager_.communicteW();
	InitGI();
	communicationManager_.communicteGI();
	InitGJ();
	communicationManager_.communicteGJ();
	InitGK();
	communicationManager_.communicteGK();

	if (parameters_.GetOutputFlag()==1) {
		output.write(0, "./output/");
	}

	for (int i = 1; i < 100; i++) {
		// print out to the log
		if (parameters_.topology.id==0) {
			std::cout << "Time Step: " << i << std::endl;
		}

		Updatem();	
		UpdateM();	
		UpdateDzI();
		communicationManager_.communicteDzI();
		UpdateDzJ();
		communicationManager_.communicteDzJ();
		UpdateDzK();
		communicationManager_.communicteDzK();
		UpdateGI();
		communicationManager_.communicteGI();
		UpdateGJ();
		communicationManager_.communicteGJ();
		UpdateGK();
		communicationManager_.communicteGK();
	
		//TODO FIX BUG communicate the 2d computational fields
		CalculateZAZI();
		communicationManager_.communicteZazi();
		CalculateZAZJ();
		communicationManager_.communicteZazj();
		CalculateZAGI();
		communicationManager_.communicteZagi();
		CalculateZAGJ();
		communicationManager_.communicteZagj();
		CalculateDelta();
		communicationManager_.communicteDelta();
		//UpdateEtta();
		ParallelUpdateEtta();
		//PetscUpdateEtta();
		communicationManager_.communicteEtta();
		UpdateU();
		communicationManager_.communicteU();
		UpdateV();
		communicationManager_.communicteV();
		UpdateW();
		communicationManager_.communicteW();

		if (parameters_.GetOutputFlag()==1) {
			output.write(i, "./output/");	
		}
	}
	//parameters_.topology.print();

/*	
	MPI_Barrier(parameters_.topology.communicator);
	for (int i = 0; i < parameters_.topology.np; i++) {
			MPI_Barrier(parameters_.topology.communicator);
			if (parameters_.topology.id == i)	
				flowField_.printGI(1);
	}
	MPI_Barrier(parameters_.topology.communicator);
*/
/*
	for (int i = 0; i < parameters_.topology.np; i++) {
		MPI_Barrier(parameters_.topology.communicator);
		if (parameters_.topology.id == i) {
						std::cout << "rank: " << i << std::endl;
		}
*/
}
