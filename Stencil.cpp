#include "Stencil.h"

Stencil::Stencil(const Parameters& parameters,const FlowField& flowField,int NumBuffers):
	Stencil_( DiscreteLine(NumBuffers,0) ),
	parameters_(parameters),
	flowField_(flowField){}

Stencil1D::Stencil1D(const Parameters& parameters, const FlowField& flowField, DiscreteLine& field):
	Stencil(parameters, flowField, 3),field_(field){}
Stencil2D::Stencil2D(const Parameters& parameters, const FlowField& flowField, DiscreteRectangle field):
	Stencil(parameters, flowField, 5), field_(field){}
Stencil3D::Stencil3D(const Parameters& parameters, const FlowField& flowField, DiscreteCube field):
	Stencil(parameters, flowField, 7), field_(field){}
BoundaryStencil1D::BoundaryStencil1D(const Parameters& parameters, const FlowField& flowField, DiscreteLine& field, DiscreteLine& boundaries):
	Stencil(parameters, flowField, 2), field_(field), boundaries_(boundaries){}
BoundaryStencil2D::BoundaryStencil2D(const Parameters& parameters, const FlowField& flowField, DiscreteRectangle field, DiscreteRectangle& boundaries):
	Stencil(parameters, flowField, 4), field_(field), boundaries_(boundaries){}
BoundaryStencil3D::BoundaryStencil3D(const Parameters& parameters, const FlowField& flowField, DiscreteCube field, DiscreteCube& boundaries):
	Stencil(parameters, flowField, 6), field_(field), boundaries_(boundaries){}

void Stencil1D::Operate(){this->Operate(0); std::cout << "bad use of stencil" << std::endl;};
void Stencil1D::Operate(int i, int j){j++; this->Operate(i); std::cout << "bad use of stencil" << std::endl;}
void Stencil1D::Operate(int i, int j, int k){j++; k++; this->Operate(i); std::cout << "bad use of stencil" << std::endl;}

void Stencil2D::Operate(){this->Operate(0,0); std::cout << "bad use of stencil" << std::endl;};
void Stencil2D::Operate(int i){this->Operate(i,0); std::cout << "bad use of stencil" << std::endl;}
void Stencil2D::Operate(int i, int j, int k){k++; this->Operate(i,j); std::cout << "bad use of stencil" << std::endl;}

void Stencil3D::Operate(){this->Operate(0,0,0); std::cout << "bad use of stencil" << std::endl;};
void Stencil3D::Operate(int i){this->Operate(i,0,0); std::cout << "bad use of stencil" << std::endl;}
void Stencil3D::Operate(int i, int j){this->Operate(i,j,0); std::cout << "bad use of stencil" << std::endl;}

void BoundaryStencil1D::Operate(int i){i++; this->Operate(); std::cout << "bad use of stencil" << std::endl;};
void BoundaryStencil1D::Operate(int i, int j){i++; j++; this->Operate(); std::cout << "bad use of stencil" << std::endl;}
void BoundaryStencil1D::Operate(int i, int j, int k){i++; j++; k++; this->Operate(); std::cout << "bad use of stencil" << std::endl;}

void BoundaryStencil2D::Operate(){this->Operate(0); std::cout << "bad use of stencil" << std::endl;};
void BoundaryStencil2D::Operate(int i, int j){j++; this->Operate(i); std::cout << "bad use of stencil" << std::endl;}
void BoundaryStencil2D::Operate(int i, int j, int k){j++; k++; this->Operate(i); std::cout << "bad use of stencil" << std::endl;}

void BoundaryStencil3D::Operate(){this->Operate(0,0); std::cout << "bad use of stencil" << std::endl;};
void BoundaryStencil3D::Operate(int i){this->Operate(i,0); std::cout << "bad use of stencil" << std::endl;}
void BoundaryStencil3D::Operate(int i, int j, int k){k++; this->Operate(i,j); std::cout << "bad use of stencil" << std::endl;}


