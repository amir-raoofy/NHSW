#include "Solver.h"

Solver::Solver(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){}

IterativeSolver::IterativeSolver(const Parameters& parameters, FlowField& flowField):
	Solver(parameters, flowField){}

void IterativeSolver::SetParameters(FLOAT TOL, int MaxIt){TOL_=TOL; MaxIt_=MaxIt;}

void Solver::set_time_step(FLOAT ts){ time_step = ts;}
