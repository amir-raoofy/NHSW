#include "Simulation.h"

int main(int argc, const char *argv[])
{
	Parameters parameters(argc, argv);
	parameters.print_parameters();
	
	FlowField flowField(parameters);
	Simulation simulation(parameters, flowField);

	simulation.Run();
	return EXIT_SUCCESS;
}
