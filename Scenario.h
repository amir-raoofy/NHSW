#pragma once
#include "Parameters.h"
#include "FlowField.h"
#include "CommunicationManager.h"

class Scenario
{
public:

	Scenario(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	virtual ~Scenario();

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

	void Init();

	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}

protected:

	const Parameters& parameters_;
	FlowField& flowField_;
	CommunicationManager& communicationManager_;

};
