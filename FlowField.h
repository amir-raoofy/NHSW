#pragma once
#include "Parameters.h"
#include "data_structure.h"

/* @breif class FlowField
 * this class abstracts the field attribute inside the domain
 * and the boundaries for the solver
 * this class stores the simulation data.
 * */

class FlowField
{
public:
	FlowField(const Parameters& parameters);
	~FlowField();
	// for debug only
	void printEtta(int it=0);
	void printm(int it=0);
	void printM(int it=0);
	void printDzI(int it=0);
	void printDzJ(int it=0);
	void printDzK(int it=0);
	void printU(int it=0);
	void printV(int it=0);
	void printW(int it=0);
	void printGI(int it=0);
	void printGJ(int it=0);
	void printGK(int it=0);
	void printZazi(int it=0);
	void printZazj(int it=0);
	void printZagi(int it=0);
	void printZagj(int it=0);
	void PrintDelta(int it=0);

	// methods	
	int* mem_allocate_2d_int();
	FLOAT* mem_allocate_2d_float();
	FLOAT* mem_allocate_3d_float();
	void init_field_2d_int(int* field);
	void init_field_2d_float(FLOAT* field);
	void init_field_3d_float(FLOAT* field);

	inline int map(const int& i, const int& j) const {return j+i*(parameters_.get_num_cells(1)+2);}
	inline int map(const int& i, const int& j, const int& k) const {return k+j*parameters_.get_num_cells(2)
										        +i*(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2);}

	// velocity
	FLOAT* u; 																	// velocity field data domain
	FLOAT* v;
	FLOAT* w;

	// g_ij
	FLOAT* g_i;																// intermediate clac. functions
	FLOAT* g_j;
	FLOAT* g_k;
	
	// dz
	FLOAT* dz_i;																// data of delta_z of all cells
	FLOAT* dz_j;
	FLOAT* dz_k;

	// elevation
	FLOAT* etta;													// free surface heaight elevation

	// intermediate buffer for elevation
	FLOAT* delta;													// intermediate buffer
	FLOAT* zaz_i;													// intermediate buffer
	FLOAT* zaz_j;													// intermediate buffer
	FLOAT* zag_i;													// intermediate buffer
	FLOAT* zag_j;													// intermediate buffer

	// higher and lower indices for 3rd dimension iteration
	int* m	;														// discretized bathymetry
	int* M	;														// discretized height of water
	
private:
	const Parameters& parameters_; 										//reference to the parameters
	const FLOAT height_	;															// reference height of water

};
