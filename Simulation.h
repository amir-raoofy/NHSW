#include "Parameters.h"
#include "FlowField.h"

class Simulation
{
public:
	Simulation(const Parameters& parameters, FlowField& flowField);
	~Simulation();

	// methods
	void InitEtta();
	void InitEttaBoundaries();
	void Initm();
	void InitM();
	void InitU();
	void InitV();
	void InitW();
	void InitQ();
	void InitDzI();
	void InitDzJ();
	void InitzAz();
	void InitGI();
	void InitGJ();
	void InitDelta();	

	void Run();
private:
	const Parameters& parameters_;
	FlowField& flowField_;
	/* data */
};
