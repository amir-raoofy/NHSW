#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"
#include "helper.h"
#include <petscksp.h>


class Solver
{
public:
	Solver(const Parameters& parameters, FlowField& flowField);
 	virtual	void solve()=0;

protected:
	const Parameters& parameters_;
	FlowField& flowField_;
	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}

};

class IterativeSolver: public Solver
{
public:	
	IterativeSolver(const Parameters& parameters, FlowField& flowField);
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

class JacobiSolverAI: public IterativeSolver
{
public:
	JacobiSolverAI(const Parameters& parameters, FlowField& flowField, FLOAT* x, FLOAT* rhs);
	~JacobiSolverAI();
	void solve();
	void SetBuffer(FLOAT* x);
	void SetRhs(FLOAT* rhs);
	void SetIndices(int i, int j);
protected:
	int i;
	int j;
	FLOAT* rhs_;
	FLOAT* x_;
	FLOAT* x_old_;
	virtual void updateDomain();
	virtual void updateBoundary();
	virtual void updateError();
	virtual void iterate();
};

class JacobiSolverAJ: public JacobiSolverAI{
public:
	JacobiSolverAJ(const Parameters& parameters, FlowField& flowField, FLOAT* x, FLOAT* rhs);
protected:
	void updateDomain();
	void updateBoundary();
};

class JacobiSolverAK: public JacobiSolverAI{
public:
	JacobiSolverAK(const Parameters& parameters, FlowField& flowField, FLOAT* x, FLOAT* rhs);
protected:
	void updateDomain();
	void updateBoundary();
};

class JacobiSolverEtta: public IterativeSolver
{
public:
	JacobiSolverEtta(const Parameters& parameters, FlowField& flowField);
	void solve();
protected:
	FLOAT* etta_old_;
	FLOAT* error_;
	void updateDomain();
	void updateBoundary();
	void updateError();
	virtual void iterate();
};

class ParallelJacobiSolverEtta: public JacobiSolverEtta
{
public:
	ParallelJacobiSolverEtta(const Parameters& parameters, FlowField& flowField, CommunicationManager &communicationManager);
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
