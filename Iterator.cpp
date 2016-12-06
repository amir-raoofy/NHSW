#include "Iterator.h"

Iterator::Iterator(const Parameters& parameters, const FlowField& flowField, Stencil& stencil):
	parameters_(parameters),
	flowField_(flowField),
	Stencil_(stencil){}

DomainIterator1D::DomainIterator1D(const Parameters& parameters, const FlowField& flowField, Stencil1D& stencil):
	Iterator(parameters, flowField, stencil){}
DomainIterator2D::DomainIterator2D(const Parameters& parameters, const FlowField& flowField, Stencil2D& stencil):
	Iterator(parameters, flowField, stencil){}
DomainIterator3D::DomainIterator3D(const Parameters& parameters, const FlowField& flowField, Stencil3D& stencil):
	Iterator(parameters, flowField, stencil){}
BoundaryIterator1D::BoundaryIterator1D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil1D& stencil):
	Iterator(parameters, flowField, stencil){}
BoundaryIterator2D::BoundaryIterator2D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	Iterator(parameters, flowField, stencil){}
BoundaryIterator3D::BoundaryIterator3D(const Parameters& parameters, const FlowField& flowField, BoundaryStencil3D& stencil):
	Iterator(parameters, flowField, stencil){}

DomainIteratorZ::DomainIteratorZ(const Parameters& parameters, const FlowField& flowField, Stencil1D& stencil):
	DomainIterator1D(parameters, flowField, stencil){}
DomainIteratorXY::DomainIteratorXY(const Parameters& parameters, const FlowField& flowField, Stencil2D& stencil):
	DomainIterator2D(parameters, flowField, stencil){}
DomainIteratorXYZ::DomainIteratorXYZ(const Parameters& parameters, const FlowField& flowField, Stencil3D& stencil):
	DomainIterator3D(parameters, flowField, stencil){}
BoundaryIteratorZ::BoundaryIteratorZ(const Parameters& parameters, const FlowField& flowField, BoundaryStencil1D& stencil):
	BoundaryIterator1D(parameters, flowField, stencil){}
BoundaryIteratorXY::BoundaryIteratorXY(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
BoundaryIteratorXYZ::BoundaryIteratorXYZ(const Parameters& parameters, const FlowField& flowField, BoundaryStencil3D& stencil):
	BoundaryIterator3D(parameters, flowField, stencil){}

void DomainIteratorZ::iterate(){}
void DomainIteratorXY::iterate(){}
void DomainIteratorXYZ::iterate(){}

void BoundaryIteratorZ::iterate(){}
void BoundaryIteratorXY::iterate(){}
void BoundaryIteratorXYZ::iterate(){}


