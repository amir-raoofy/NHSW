#include <flowField.h>

class Simulation
{
public:
	Simulation(flowField *flowfield, Parameters *parameters);
	~Simulation();
	void run();

private:
	/* data */
	Parameters *_parameters;
	flowField  *_flowfield;
};
