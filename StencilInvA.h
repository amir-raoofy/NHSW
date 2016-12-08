#pragma once
#include "Stencil.h"

class StencilInvA: public Stencil
{
public:
	StencilInvA(const Parameters& parameters,const FlowField& flowField);
	virtual void Operate(int i=0, int j=0, int k=0);
};
