#include "Parameters.h"
#include "FlowField.h"
#include "Solver.h"
#include "Scenario.h"
#include "CommunicationManager.h"
#include "Simulation.h"

class PetscSimulation : public Simulation
{
public:

	PetscSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	virtual ~PetscSimulation();

	void UpdateU();
	void UpdateV();
	void UpdateEtta();
	
	void CalculateZAZI();
	void CalculateZAZJ();
	void CalculateZAGI();
	void CalculateZAGJ();

protected:
	
	Petsc1DSolver* petsc_solver_1d_Ai_;
	Petsc1DSolver* petsc_solver_1d_Aj_;
	Petsc1DSolverU* petsc_solver_1d_u_Ai_;
	Petsc1DSolverU* petsc_solver_1d_v_Aj_;

};
