#include "Parameters.h"
#include "FlowField.h"

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
	void iterate();
};

