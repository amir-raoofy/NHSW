#include "Simulation.h"
#include "Topology.h"
#include <petscksp.h>

int main(int argc, char *argv[])
{
	
	Topology topology(argc,argv);
	Parameters parameters(argc, argv, topology);
	PetscInitialize(0, NULL,0,NULL);
	FlowField flowField(parameters);
	CommunicationManager communicationManager (parameters,flowField);
	Simulation simulation(parameters, flowField, communicationManager);
	simulation.Run();
	
	PetscFinalize();
	return EXIT_SUCCESS;
}
