#include "Simulation.h" 

void Simulation::Run(){
	InitEtta();
	InitEttaBoundaries();
	Initm();
	InitM();
	InitDzI();
	InitDzJ();
	InitzAz();
}
