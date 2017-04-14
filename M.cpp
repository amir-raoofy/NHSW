#include "Simulation.h"

void Simulation::UpdateM(){
				
	scenario_->InitM();
	scenario_->updateBoundariesM();

}
