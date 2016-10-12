// This class contains the abstraction and the signatures of linear equation solvers. 
// solves Ax=b

class Solver
{
protected:
	float* _A;	// Matrix A
	float* _b;	// Right hand-side b
	float* _x;	// solution of the equation
	int  _N;	// size of the linear system

public:
	Solver(float* A, float*b, float*x, int N) : _A(A), _b(b), _x(x), _N(N){};
	virtual void solve(float TOL, int MaxIt)=0;
};

class Jacobi : public Solver
{
private:
	float* x_old;	// buffer to store the solution after each iteration
	float* r;		// residual
	float _res;		// norm of residual

	void iterate();
	void update_residual();

public:
	Jacobi(float* A, float*b, float*x, int N);
	void solve(float TOL, int MaxIt);
	void set_A_and_b(float* A, float* b);
	~Jacobi();
};
