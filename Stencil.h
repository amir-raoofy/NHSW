#include "Parameters.h"
#include "FlowField.h"
#include "data_structure.h"

class Stencil
{
public:
	Stencil(const Parameters& parameters,const FlowField& flowField, int NumBuffers);
protected:
	DiscreteLine Stencil_;
	const Parameters& parameters_;
	const FlowField& flowField_;
	virtual void Operate() = 0;
	virtual void Operate(int i) = 0;
	virtual void Operate(int i, int j) = 0;
	virtual void Operate(int i, int j, int k) = 0;
};

class Stencil1D: public	Stencil
{
public:
	Stencil1D(const Parameters& parameters, const FlowField& flowField, DiscreteLine& field);
private:
	virtual void Operate();
	virtual void Operate(int i) = 0;
	virtual void Operate(int i, int j);
	virtual void Operate(int i, int j, int k);
DiscreteLine& field_;
};

class Stencil2D: public	Stencil
{
public:
	Stencil2D(const Parameters& parameters, const FlowField& flowField, DiscreteRectangle field);
private:
	virtual void Operate();
	virtual void Operate(int i);
	virtual void Operate(int i, int j) = 0;
	virtual void Operate(int i, int j, int k);
	DiscreteRectangle field_;
};

class Stencil3D: public	Stencil
{
public:
	Stencil3D(const Parameters& parameters, const FlowField& flowField, DiscreteCube field);
private:
	virtual void Operate();
	virtual void Operate(int i);
	virtual void Operate(int i, int j);
	virtual void Operate(int i, int j, int k) = 0;
	DiscreteCube field_;
};

class BoundaryStencil1D: public	Stencil{
public:
	BoundaryStencil1D(const Parameters& parameters, const FlowField& flowField, DiscreteLine& field, DiscreteLine& boundaries);
private:
	virtual void Operate() = 0;
	virtual void Operate(int i);
	virtual void Operate(int i, int j);
	virtual void Operate(int i, int j, int k);
	DiscreteLine& field_;
	DiscreteLine& boundaries_;
};

class BoundaryStencil2D: public	Stencil
{
public:
	BoundaryStencil2D(const Parameters& parameters, const FlowField& flowField, DiscreteRectangle field, DiscreteRectangle& boundaries);
private:
	virtual void Operate();
	virtual void Operate(int i) = 0;
	virtual void Operate(int i, int j);
	virtual void Operate(int i, int j, int k);
	DiscreteRectangle field_;
	DiscreteRectangle& boundaries_;
};

class BoundaryStencil3D: public	Stencil
{
public:
	BoundaryStencil3D(const Parameters& parameters, const FlowField& flowField, DiscreteCube field, DiscreteCube& boundaries);
private:
	virtual void Operate();
	virtual void Operate(int i);
	virtual void Operate(int i, int j) = 0;
	virtual void Operate(int i, int j, int k);
	DiscreteCube field_;
	DiscreteCube& boundaries_;
};