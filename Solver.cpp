#include "Solver.h"

Solver::Solver(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){}

IterativeSolver::IterativeSolver(const Parameters& parameters, FlowField& flowField):
	Solver(parameters, flowField){}


