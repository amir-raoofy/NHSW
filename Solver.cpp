#include "Solver.h"

//Solver
Solver::Solver(const Parameters& parameters, FlowField& flowField):
	parameters_(parameters),
	flowField_(flowField){}

Solver::~Solver(){}

void Solver::set_time_step(FLOAT ts){ time_step = ts;}

FLOAT Solver::get_spent_time() const{
	return time_;	
}

int Solver::get_iterations() const{
	return it_;
}


//Iterative solver
IterativeSolver::IterativeSolver(const Parameters& parameters, FlowField& flowField):
	Solver(parameters, flowField){}

IterativeSolver::~IterativeSolver(){}

void IterativeSolver::SetParameters(FLOAT TOL, int MaxIt){TOL_=TOL; MaxIt_=MaxIt;}

//jacobi iterative solver in 1d
JacobiIterativeSolver1D::JacobiIterativeSolver1D(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old):
	IterativeSolver(parameters, flowField),
	rhs_(rhs), 
	x_(x),
	x_old_(x_old){}

JacobiIterativeSolver1D::~JacobiIterativeSolver1D(){}

void JacobiIterativeSolver1D::SetIndices(int i, int j){this->i=i; this->j=j;}

void JacobiIterativeSolver1D::SetBuffer(FLOAT* x){

	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		x_[k] =	x[map(i,j,k)];
	}

	memcpy ( x_old_, x_, parameters_.get_num_cells(2) );

}

void JacobiIterativeSolver1D::SetRhs(FLOAT* rhs){

	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		rhs_[k] = rhs[map(i,j,k)];
	}

}

