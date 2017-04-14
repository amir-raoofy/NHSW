#pragma once
#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"

class Scenario
{
public:

	Scenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	virtual ~Scenario();
	
	void Init(); // driver method for initialization of the data

	virtual void InitU()=0;
	virtual void InitV()=0;
	virtual void InitW()=0;
	virtual void InitEtta()=0;

	virtual void Initm()=0;
	virtual void InitM()=0;

	virtual void InitDzI()=0;
	virtual void InitDzJ()=0;
	virtual void InitDzK()=0;
	virtual void InitGI()=0;
	virtual void InitGJ()=0;
	virtual void InitGK()=0;

	virtual void updateBoundariesDzI()=0;
	virtual void updateBoundariesDzJ()=0;
	virtual void updateBoundariesDzK()=0;
	virtual void updateBoundariesGI()=0;
	virtual void updateBoundariesGJ()=0;
	virtual void updateBoundariesGK()=0;
	virtual void updateBoundariesZAZI()=0;
	virtual void updateBoundariesZAZJ()=0;
	virtual void updateBoundariesZAGI()=0;
	virtual void updateBoundariesZAGJ()=0;
	virtual void updateBoundariesDelta()=0;
	virtual void updateBoundariesEtta()=0;
	virtual void updateBoundariesU()=0;
	virtual void updateBoundariesV()=0;
	virtual void updateBoundariesW()=0;
	

	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}

protected:

	const Parameters& parameters_;
	FlowField& flowField_;
	CommunicationManager& communicationManager_;

};
