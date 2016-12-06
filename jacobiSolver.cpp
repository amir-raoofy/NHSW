#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>

// constructor
Jacobi::Jacobi(float* A, float*b, float*x, int N) : matrixSolver(A, b, x, N){
	x_old= new float [_N];
	r= new float [_N];
	std::cout << "\033[1;31m====Jacobi solver is invoked====\033[0m"	<< std::endl;
}

// destructor
Jacobi::~Jacobi(){
	delete [] x_old;
	delete [] r;
}

// main loop of the iterative solve; one iteration of Jacobi
void Jacobi::iterate(){
	int i, j;
	float sum = 0;
	for (i = 0; i < _N; i++) {
		sum = 0;
		for (j = 0; j < i; j++) {
			sum += _A [j+ i*_N] * x_old[j];
		}
		for (j = i+1; j < _N; j++) {
			sum += _A[j+i*_N] * x_old[j];
		}
		_x[i] = (_b[i]-sum)/_A[i+i*_N];
	}
	memcpy(x_old, _x, _N * sizeof(float));
	update_residual();
}

// calculation of the residual
void Jacobi::update_residual(){
	int i, j;
	float sum = 0;
	memcpy(x_old, _x, _N * sizeof(float));
	for (i = 0; i < _N; i++) {
		r[i] = 0;
		for (j = 0; j < _N; j++) {
			r[i] += _A [j+ i*_N] * x_old[j];
		}
		r[i]-=_b[i];
	}

	/*
	 *for (i = 0; i < _N; i++) {
	 *  std::cout << r[i] << "\t" << std::endl;
	 *}
	 */

	sum = 0;
	for (i = 0; i < _N; i++) {
		sum+=r[i]*r[i];
	}
	_res = sqrt (sum)/_N;
}

// solve method
void Jacobi::solve(float TOL, int MaxIt){
	int i=0;
	update_residual();
	while (_res>TOL && i<MaxIt){
		iterate();
		i++;
	}
	if (i==MaxIt)
		std::cout << "\033[1;31mWARNING\033[0m: solver did not converge; maximum number of iterations was reached." << std::endl;
	else
		std::cout << "Jacobi solver converged after " << i << " iterations, the value of residual is "<< _res << std::endl;

}

void Jacobi::set_A_and_b(float* A, float* b){
		this->_A = A;
		this->_b = b;
}
