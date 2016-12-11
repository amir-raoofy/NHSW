#include "Simulation.h" 

void Simulation::Run(){
	InitEtta();
//	InitEttaBoundaries();
	Initm();
	InitM();
	InitU();
	InitV();
	InitW();
	InitQ();
	InitDzI();
	InitDzJ();
	InitzAz();
	InitGI();
	InitGJ();
	InitDelta();
}
