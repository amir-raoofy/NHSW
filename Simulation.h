#pragma once
#include "Parameters.h"
#include "FlowField.h"
#include "Solver.h"
#include "Scenario.h"
#include "CommunicationManager.h"

class Simulation
{
public:

	Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager);
	virtual ~Simulation();

	virtual void UpdateU()=0;
	virtual void UpdateV()=0;
	void UpdateW();
	virtual void UpdateEtta()=0;
	
	void Updatem();
	void UpdateM();
	
	void UpdateDzI();
	void UpdateDzJ();
	void UpdateDzK();
	void UpdateGI();
	void UpdateGJ();
	void UpdateGK();
	void CalculateDelta();	
	virtual void CalculateZAZI()=0;
	virtual void CalculateZAZJ()=0;
	virtual void CalculateZAGI()=0;
	virtual void CalculateZAGJ()=0;

	void UpdateSimulationTimeStep();

	void Run();

	void printTimeMeasurements();

	inline int map(int i, int j) { return flowField_.map(i,j);}
	inline int map(int i, int j, int k) { return flowField_.map(i,j,k);}

protected:

	const Parameters& parameters_;
	FlowField& flowField_;
	Scenario* scenario_;
	CommunicationManager& communicationManager_;
	FLOAT time_step;
	FLOAT time=0.0;
	//measurements
	FLOAT T1=0.0,T2=0.0,T3=0.0,T4=0.0,T5=0.0;

};
