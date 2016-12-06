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

/*DomainIteratorZ::DomainIteratorZ(const Parameters& parameters, const FlowField& flowField, Stencil1D& stencil):
	DomainIterator1D(parameters, flowField, stencil){}
*/
DomainIteratorXY::DomainIteratorXY(const Parameters& parameters, const FlowField& flowField, Stencil2D& stencil):
	DomainIterator2D(parameters, flowField, stencil){}
DomainIteratorXYZ::DomainIteratorXYZ(const Parameters& parameters, const FlowField& flowField, Stencil3D& stencil):
	DomainIterator3D(parameters, flowField, stencil){}
BoundaryIteratorX::BoundaryIteratorX(const Parameters& parameters, const FlowField& flowField, BoundaryStencil1D& stencil):
	BoundaryIterator1D(parameters, flowField, stencil){}
BoundaryIteratorY::BoundaryIteratorY(const Parameters& parameters, const FlowField& flowField, BoundaryStencil1D& stencil):
	BoundaryIterator1D(parameters, flowField, stencil){}

BoundaryIteratorXY::BoundaryIteratorXY(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
BoundaryIteratorLeft::BoundaryIteratorLeft(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
BoundaryIteratorRight::BoundaryIteratorRight(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
BoundaryIteratorBack::BoundaryIteratorBack(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
BoundaryIteratorFront::BoundaryIteratorFront(const Parameters& parameters, const FlowField& flowField, BoundaryStencil2D& stencil):
	BoundaryIterator2D(parameters, flowField, stencil){}
/*
BoundaryIteratorXYZ::BoundaryIteratorXYZ(const Parameters& parameters, const FlowField& flowField, BoundaryStencil3D& stencil):
	BoundaryIterator3D(parameters, flowField, stencil){}
*/

void DomainIteratorXY::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			Stencil_.Operate(i,j);
		}
	}
}

void DomainIteratorXYZ::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			for (int k = flowField_.Getm()[i][j]; k < flowField_.GetM()[i][j]; k++) {
				Stencil_.Operate(i,j,k);
			}
		}
	}
}

void BoundaryIteratorX::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		Stencil_.Operate(i);
	}
}

void BoundaryIteratorY::iterate(){
	for (int j = 0; j < parameters_.get_num_cells(1); j++) {
		Stencil_.Operate(j);
	}
}

void BoundaryIteratorXY::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			Stencil_.Operate(i,j);
		}
	}
}

void BoundaryIteratorBack::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int k = flowField_.Getm()[i][0]; k < flowField_.GetM()[i][0]; k++) {
			Stencil_.Operate(i,k);
		}
	}
}

void BoundaryIteratorFront::iterate(){
	for (int i = 0; i < parameters_.get_num_cells(0); i++) {
		for (int k = flowField_.Getm()[i][parameters_.get_num_cells(1)-1]; k < flowField_.GetM()[i][parameters_.get_num_cells(1)-1]; k++) {
			Stencil_.Operate(i,k);
		}
	}
}
void BoundaryIteratorLeft::iterate(){
	for (int j = 0; j < parameters_.get_num_cells(1); j++) {
		for (int k = flowField_.Getm()[0][j]; k < flowField_.GetM()[0][j]; k++) {
			Stencil_.Operate(j,k);
		}
	}
}

void BoundaryIteratorRight::iterate(){
	for (int j = 0; j < parameters_.get_num_cells(1); j++) {
		for (int k = flowField_.Getm()[parameters_.get_num_cells(0)-1][j]; k < flowField_.GetM()[parameters_.get_num_cells(0)-1][j]; k++) {
			Stencil_.Operate(j,k);
		}
	}
}
/*
void BoundaryIteratorXYZ::iterate(){
}
*/
