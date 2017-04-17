#include "Simulation.h" 
#include "Solver.h"
#include "output.h"

void Simulation::Run(){

	Output output(parameters_, flowField_);

	scenario_ -> Init();

	if (parameters_.GetOutputFlag()==1) {
		output.write(0, "./output/");
	}

	//main loop -> proceed in time 
	for (int i=1; time <= parameters_.get_sim_time() && i< parameters_.get_max_ts(); i++) {
			
		// print out to the log
		if (parameters_.topology.id==0) {
			if (parameters_.GetOutputFlag()==1) 
				std::cout << "Time Step:" << i << ", simulation time:" << time+time_step << ", dt:" << time_step << std::endl;
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
		UpdateEtta();
		communicationManager_.communicteEtta();
		UpdateU();
		communicationManager_.communicteU();
		UpdateV();
		communicationManager_.communicteV();
		UpdateW();
		communicationManager_.communicteW();
		
		UpdateSimulationTimeStep();
		time+=time_step;

		if (parameters_.GetOutputFlag()==1) {
			if (i%parameters_.GetOutFreq()==0) 	
				output.write(i, "./output/");	
		}
	}

}
