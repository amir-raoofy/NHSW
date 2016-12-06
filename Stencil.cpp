#include "Stencil.h"

Stencil::Stencil(const Parameters& parameters,const FlowField& flowField,int NumBuffers):
	Stencil_( DiscreteLine(NumBuffers,0) ),
	parameters_(parameters),
	flowField_(flowField){}
std::vector<float>& Stencil::SetStencil(){return Stencil_;}
const std::vector<float>& Stencil::GetStencil() const{return Stencil_;}

Stencil1D::Stencil1D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 3){}
Stencil2D::Stencil2D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 5){}
Stencil3D::Stencil3D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 7){}
BoundaryStencil1D::BoundaryStencil1D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 2){}
BoundaryStencil2D::BoundaryStencil2D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 4){}
BoundaryStencil3D::BoundaryStencil3D(const Parameters& parameters,const FlowField& flowField):
	Stencil(parameters, flowField, 6){}
