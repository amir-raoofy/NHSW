#include "Parameters.h"
#include "FlowField.h"
#include "data_structure.h"

class Stencil
{
public:
	Stencil(const Parameters& parameters,const FlowField& flowField, int NumBuffers);
	//setter and getter
	DiscreteLine& SetStencil(); 
	const DiscreteLine& GetStencil() const; 

protected:
	DiscreteLine Stencil_;
	const Parameters& parameters_;
	const FlowField& flowField_;
private:
	
};

class Stencil1D: public	Stencil
{
public:
	Stencil1D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteLine& field, int i) = 0;
};

class Stencil2D: public	Stencil
{
public:
	Stencil2D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteRectangle& field, int i, int j) = 0;
};

class Stencil3D: public	Stencil
{
public:
	Stencil3D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteCube& field, int i, int j, int k) = 0;
};

class BoundaryStencil1D: public	Stencil{
public:
	BoundaryStencil1D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteLine& field, FLOAT Boundary) = 0;
};

class BoundaryStencil2D: public	Stencil
{
public:
	BoundaryStencil2D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteRectangle& field, DiscreteLine Boundary, int i) = 0;
};

class BoundaryStencil3D: public	Stencil
{
public:
	BoundaryStencil3D(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(DiscreteCube& field, DiscreteRectangle Boundary, int i, int j) = 0;
};
