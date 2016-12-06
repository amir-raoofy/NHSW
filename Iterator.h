#include "Stencil.h"

class Iterator
{
public:
	Iterator(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	virtual void iterate() = 0;
private:
	const Parameters& parameters_;
	const FlowField& flowField_;
protected:
	Stencil& Stencil_;
};

class DomainIterator1D: public Iterator
{
public:
	DomainIterator1D(const Parameters& parameters, const FlowField& flowField, Stencil1D& stencil);
	void iterate() = 0;
};

class DomainIterator2D: public Iterator
{
public:
	DomainIterator2D(const Parameters& parameters, const FlowField& flowField, Stencil2D& stencil);
	void iterate() = 0;
};

class DomainIterator3D: public Iterator
{
public:
	DomainIterator3D(const Parameters& parameters, const FlowField& flowField, Stencil3D& stencil);
	void iterate() = 0;
};

class BoundaryIterator1D: public Iterator
{
public:
	BoundaryIterator1D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil1D& stencil);
	void iterate() = 0;
};

class BoundaryIterator2D: public Iterator
{
public:
	BoundaryIterator2D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil);
	void iterate() = 0;
};

class BoundaryIterator3D: public Iterator
{
public:
	BoundaryIterator3D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil3D& stencil);
	void iterate() = 0;
};
