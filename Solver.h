#include "Parameters.h"
#include "FlowField.h"

class Solver
{
public:
	Solver(const Parameters& Parameters, FlowField& flowField);
 	virtual	void solve()=0;

protected:
	const Parameters& parameters_;
	FlowField& flowField_;
};

class IterativeSolver: public Solver
{
public:	
	IterativeSolver(const Parameters& Parameters, FlowField& flowField);
	void SetParameters(float TOL, int MaxIt);
protected:
	FLOAT TOL_;
	int MaxIt_;
	FLOAT err_;
private:
	virtual void iterate()=0;
};

class JacobiSolverAI: public IterativeSolver
{
public:
	JacobiSolverAI(const Parameters& Parameters, FlowField& flowField, DiscreteLine& x);
	void solve();
	void SetBuffer(DiscreteLine& x);
	void SetIndices(int i, int j);
protected:
	int i_;
	int j_;
	DiscreteLine& x_;
	DiscreteLine x_old_;
	DiscreteLine error_;
	virtual void updateDomain();
	virtual void updateBoundary();
	void updateError();
	void iterate();
};


class JacobiSolverAJ: public JacobiSolverAI{
public:
	JacobiSolverAJ(const Parameters& Parameters, FlowField& flowField, DiscreteLine& x);
protected:
	void updateDomain();
	void updateBoundary();
};
