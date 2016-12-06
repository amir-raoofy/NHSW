#include "Stencil.h"

class Iterator
{
public:
	Iterator(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	virtual void iterate() = 0;
protected:
	const Parameters& parameters_;
	const FlowField& flowField_;
	Stencil& Stencil_;
};
/*
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
*/
/*
class DomainIteratorZ: public DomainIterator1D
{
public:
	DomainIteratorZ(const Parameters& parameters, const FlowField& flowField, Stencil1D& stencil);
	void iterate();
};
*/

class DomainIteratorXY: public Iterator
{
public:
	DomainIteratorXY(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
}; 

class DomainIteratorXYZ: public Iterator
{
public:
	DomainIteratorXYZ(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorX: public Iterator
{
public:
	BoundaryIteratorX(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorY: public Iterator
{
public:
	BoundaryIteratorY(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorXY: public Iterator
{
public:
	BoundaryIteratorXY(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorLeft: public Iterator
{
public:
	BoundaryIteratorLeft(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorRight: public Iterator
{
public:
	BoundaryIteratorRight(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorBack: public Iterator
{
public:
	BoundaryIteratorBack(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};

class BoundaryIteratorFront: public Iterator
{
public:
	BoundaryIteratorFront(const Parameters& parameters, const FlowField& flowField, Stencil& stencil);
	void iterate();
};
