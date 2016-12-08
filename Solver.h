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
	void SetParameters(float TOL, int MaxIt);
private:
	FLOAT TOL_;
	int MaxIt_;
	int i_;
	int j_;
	FLOAT err_;
	DiscreteLine& x_;
	DiscreteLine x_old_;
	DiscreteLine error_;
	void updateDomain();
	void updateBoundary();
	void updateError();
	void iterate();
};
