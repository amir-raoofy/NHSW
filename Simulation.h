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
	void InitDzI();
	void InitDzJ();
	void InitzAz();
	void UpdateU();
	void UpdateV();
	void UpdateW();
	
	void Run();
private:
	const Parameters& parameters_;
	FlowField& flowField_;
	/* data */
};
