#include "FlowField.h"
#include "PetscSimulation.h"
#include "ParallelSimulation.h"
#include "Topology.h"
#include <petscksp.h>

int main(int argc, char *argv[]){

	Topology topology(argc,argv);
	Parameters parameters(argc, argv, topology);
	FlowField flowField(parameters);

	CommunicationManager communicationManager (parameters,flowField);

	Simulation* simulation=NULL;
	
	if (parameters.get_solver_type() == "PARALLEL") 
		simulation = new ParallelSimulation (parameters, flowField, communicationManager);
	else if (parameters.get_solver_type() == "PETSC") 
		simulation = new PetscSimulation (parameters, flowField, communicationManager);

	simulation->Run();
	
	return EXIT_SUCCESS;
}
