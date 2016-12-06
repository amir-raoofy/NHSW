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
