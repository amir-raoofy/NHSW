#include <simulation.h>

int main(int argc, const char *argv[])
{
	//Parameters* parameters = new Parameters();
	Parameters* parameters = new Parameters(argc, argv);
	flowField* flowfield = new flowField(parameters);
	Simulation * simulation = new Simulation(flowfield,parameters);
	
	parameters -> print_parameters();
	simulation -> run();

	delete parameters, flowfield, simulation;

	return 0;
}
