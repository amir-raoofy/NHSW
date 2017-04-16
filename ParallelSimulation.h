#include "Parameters.h"
#include "FlowField.h"
#include "Solver.h"
#include "Scenario.h"
#include "CommunicationManager.h"
#include "Simulation.h"

class ParallelSimulation : public Simulation
{
public:

	ParallelSimulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	virtual ~ParallelSimulation();

	void UpdateU();
	void UpdateV();
	void UpdateEtta();
	
	void CalculateZAZI();
	void CalculateZAZJ();
	void CalculateZAGI();
	void CalculateZAGJ();

private:
	
	//1d solver buffers
	FLOAT* rhs_;
	FLOAT* x_;
	FLOAT* x_old_;
	JacobiIterativeSolver1D* solver_1d_Ai_;
	JacobiIterativeSolver1D* solver_1d_Aj_;
	ParallelJacobiSolverEtta* etta_solver_;
};
