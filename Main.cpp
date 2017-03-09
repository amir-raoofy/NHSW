#include "Simulation.h"
#include <petscksp.h>

int main(int argc, const char *argv[])
{
	
	Parameters parameters(argc, argv);
	parameters.print_parameters();
	PetscInitialize(0, NULL,0,NULL);
	
	FlowField flowField(parameters);
	Simulation simulation(parameters, flowField);
	simulation.Run();
	
	PetscFinalize();
	return EXIT_SUCCESS;
}
