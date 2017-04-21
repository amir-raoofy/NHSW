#pragma once
#include "Parameters.h"
#include "FlowField.h"

class CommunicationManager
{
public:
	CommunicationManager(const Parameters& parameters, FlowField& flowField);
	~CommunicationManager();
	
	void communicteEtta();
	void communicteU();
	void communicteV();
	void communicteW();
	void communicteDzI();
	void communicteDzJ();
	void communicteDzK();
	void communicteGI();
	void communicteGJ();
	void communicteGK();
	void communicteZazi();
	void communicteZazj();
	void communicteZagi();
	void communicteZagj();
	void communicteDelta();

private:
	const Parameters& parameters_;
	FlowField& flowField_;

	FLOAT* right_send_buffer_line;
	FLOAT* left_send_buffer_line;
	FLOAT* front_send_buffer_line;
	FLOAT* back_send_buffer_line;
	FLOAT* right_recv_buffer_line;
	FLOAT* left_recv_buffer_line;
	FLOAT* front_recv_buffer_line;
	FLOAT* back_recv_buffer_line;

	FLOAT* right_send_buffer_rectangle;
	FLOAT* left_send_buffer_rectangle;
	FLOAT* front_send_buffer_rectangle;
	FLOAT* back_send_buffer_rectangle;
	FLOAT* right_recv_buffer_rectangle;
	FLOAT* left_recv_buffer_rectangle;
	FLOAT* front_recv_buffer_rectangle;
	FLOAT* back_recv_buffer_rectangle;

	void updateRightNeighbour2d(FLOAT* field);
	void updateLeftNeighbour2d(FLOAT* field);
	void updateFrontNeighbour2d(FLOAT* field);
	void updateBackNeighbour2d(FLOAT* field);

	void updateRightNeighbour3d(FLOAT* field);
	void updateLeftNeighbour3d(FLOAT* field);
	void updateFrontNeighbour3d(FLOAT* field);
	void updateBackNeighbour3d(FLOAT* field);

	inline int map(const int& i, const int& j) const { return flowField_.map(i,j);}
	inline int map(const int& i, const int& j, const int& k) const  { return flowField_.map(i,j,k);}

};
