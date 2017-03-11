#include "Simulation.h"
#include "Topology.h"
#include <petscksp.h>

int main(int argc, char *argv[])
{
	
	Topology topology(argc,argv);
	Parameters parameters(argc, argv, topology);
	//PetscInitialize(0, NULL,0,NULL);
	
	FlowField flowField(parameters);
	Simulation simulation(parameters, flowField);
	simulation.Run();
	
	//PetscFinalize();
	return EXIT_SUCCESS;
}
