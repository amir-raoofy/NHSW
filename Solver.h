#pragma once
#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"
#include "helper.h"
#include <petscksp.h>
#include "Scenario.h"

class Solver
{
public:
	Solver(const Parameters& parameters, FlowField& flowField );
	virtual ~Solver();
 	virtual	void solve()=0;
	void set_time_step(FLOAT ts);

protected:
	const Parameters& parameters_;
	FlowField& flowField_;
	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}
	FLOAT time_step=parameters_.get_time_step();

};

class IterativeSolver: public Solver
{
public:	
	IterativeSolver(const Parameters& parameters, FlowField& flowField);
	virtual ~IterativeSolver();
	void SetParameters(FLOAT TOL, int MaxIt);

protected:
	FLOAT TOL_;
	int MaxIt_;
	FLOAT err_;
private:
	virtual void updateDomain()=0;
	virtual void updateBoundary()=0;
	virtual void updateError()=0;
	virtual void iterate()=0;
};

class JacobiIterativeSolver1D: public IterativeSolver
{
public:
	JacobiIterativeSolver1D(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old);
	virtual ~JacobiIterativeSolver1D();
	void SetIndices(int i, int j);
	void SetBuffer(FLOAT* x);
	void SetRhs(FLOAT* rhs);
protected:
	int i;
	int j;
	FLOAT* rhs_;
	FLOAT* x_;
	FLOAT* x_old_;

};

class JacobiSolverAI: public JacobiIterativeSolver1D
{
public:
	JacobiSolverAI(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old);
	virtual ~JacobiSolverAI();
	void solve();
protected:
	virtual void updateDomain();
	virtual void updateBoundary();
	virtual void updateError();
	virtual void iterate();
};

class JacobiSolverAJ: public JacobiSolverAI{
public:
	JacobiSolverAJ(const Parameters& parameters, FlowField& flowField, FLOAT* rhs, FLOAT* x, FLOAT* x_old);
	virtual ~JacobiSolverAJ();
protected:
	void updateDomain();
	void updateBoundary();
};

class JacobiSolverEtta: public IterativeSolver
{
public:
	JacobiSolverEtta(const Parameters& parameters, FlowField& flowField, Scenario& scenario);
	void solve();
protected:
	FLOAT* etta_old_;
	FLOAT* error_;
	Scenario& scenario_;
	void updateDomain();
	void updateBoundary();
	void updateError();
	virtual void iterate();
};

class ParallelJacobiSolverEtta: public JacobiSolverEtta
{
public:
	ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager, Scenario& scenario);
protected:
	void iterate();
	void parallelUpdateError();
private: 
	CommunicationManager &communicationManager_;
};

class PetscSolver: public Solver
{
public:
	PetscSolver(const Parameters& parameters, FlowField& flowField);
	~PetscSolver();

	virtual void updateMat() = 0;
	virtual void updateRHS() = 0;
	virtual	void solve() = 0;	
	virtual void updateField() = 0;
	void setParameters(FLOAT TOL, int MaxIt);

protected:
	Vec            x,b;  
	Mat            A;      
	KSP            ksp;    
	PetscInt       i,j,Ii,J,Istart,Iend,m,n,its;

	FLOAT TOL_;
	int MaxIt_;
};


class Petsc1DSolver: public PetscSolver
{
public:

	Petsc1DSolver(const Parameters& parameters, FlowField& flowField, FLOAT* Dz, FLOAT* RHS, FLOAT* resultField);
	~Petsc1DSolver();
	
	void updateMat();
	void updateRHS();
	void solve();	
	void updateField();
	void setIndices(int i, int j);

protected:
	PetscErrorCode ierr;
	PetscScalar    v;

	FLOAT* Dz_;
	FLOAT* RHS_;
	FLOAT* resultField_;
	int i;
	int j;
};

class Petsc2DSolver: public PetscSolver
{
public:

	Petsc2DSolver(const Parameters& parameters, FlowField& flowField);
	~Petsc2DSolver();
	
	void updateMat();
	void updateRHS();
	void solve();	
	void updateField();

protected:
	PetscErrorCode ierr;
	PetscScalar    v;
};
