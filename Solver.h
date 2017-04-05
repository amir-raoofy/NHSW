#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"
#include <petscksp.h>

class Solver
{
public:
	Solver(const Parameters& parameters, FlowField& flowField);
 	virtual	void solve()=0;

protected:
	const Parameters& parameters_;
	FlowField& flowField_;
};

class IterativeSolver: public Solver
{
public:	
	IterativeSolver(const Parameters& parameters, FlowField& flowField);
	void SetParameters(float TOL, int MaxIt);
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
	JacobiSolverAI(const Parameters& parameters, FlowField& flowField, DiscreteLine& x, DiscreteLine& rhs);
	void solve();
	void SetBuffer(DiscreteLine& x);
	void SetRhs(DiscreteLine& rhs);
	void SetIndices(int i, int j);
protected:
	int i_;
	int j_;
	DiscreteLine& rhs_;
	DiscreteLine& x_;
	DiscreteLine x_old_;
	DiscreteLine error_;
	virtual void updateDomain();
	virtual void updateBoundary();
	virtual void updateError();
	virtual void iterate();
};

class JacobiSolverAJ: public JacobiSolverAI{
public:
	JacobiSolverAJ(const Parameters& parameters, FlowField& flowField, DiscreteLine& x, DiscreteLine& rhs);
protected:
	void updateDomain();
	void updateBoundary();
};

class JacobiSolverAK: public JacobiSolverAI{
public:
	JacobiSolverAK(const Parameters& parameters, FlowField& flowField, DiscreteLine& x, DiscreteLine& rhs);
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
	DiscreteRectangle etta_old_;
	DiscreteRectangle error_;
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

class JacobiSolverQ: public IterativeSolver
{
public:
	JacobiSolverQ(const Parameters& parameters, FlowField& flowField);
	void solve();
protected:
	DiscreteCube Q_old_;
	DiscreteCube error_;
	void updateDomain();
	void updateBoundary();
	void updateError();
	void iterate();
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
	void setParameters(float TOL, int MaxIt);

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

	Petsc1DSolver(const Parameters& parameters, FlowField& flowField, const DiscreteCube& Dz, const DiscreteCube& RHS, DiscreteRectangle& resultField);
	~Petsc1DSolver();
	
	void updateMat();
	void updateRHS();
	void solve();	
	void updateField();
	void setIndices(int i, int j);

protected:
	PetscErrorCode ierr;
	PetscScalar    v;

	const DiscreteCube& Dz_;
	const DiscreteCube& RHS_;
	DiscreteRectangle& resultField_;
	int i_;
	int j_;
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
