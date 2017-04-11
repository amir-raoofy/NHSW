#include "FlowField.h"
#include <omp.h>

FlowField::FlowField(const Parameters& parameters):
	parameters_(parameters),
	height_(	parameters_.GetHeight())
{

	// memory allocation
	u=mem_allocate_3d_float();
	v=mem_allocate_3d_float();
	w=mem_allocate_3d_float();
	etta=mem_allocate_2d_float();

	m=mem_allocate_2d_int();
	M=mem_allocate_2d_int();

	dz_i=mem_allocate_3d_float();
	dz_j=mem_allocate_3d_float();
	dz_k=mem_allocate_3d_float();
	g_i=mem_allocate_3d_float();
	g_j=mem_allocate_3d_float();
	g_k=mem_allocate_3d_float();

	delta=mem_allocate_2d_float();
	zaz_i=mem_allocate_2d_float();
	zaz_j=mem_allocate_2d_float();
	zag_i=mem_allocate_2d_float();
	zag_j=mem_allocate_2d_float();

	// data initialization
	init_field_3d_float(u);
	init_field_3d_float(v);
	init_field_3d_float(w);
	init_field_2d_float(etta);

	init_field_2d_int(m);
	init_field_2d_int(M);

	init_field_3d_float(dz_i);
	init_field_3d_float(dz_j);
	init_field_3d_float(dz_k);
	init_field_3d_float(g_i);
	init_field_3d_float(g_j);
	init_field_3d_float(g_k);

	init_field_2d_float(delta);
	init_field_2d_float(zaz_i);
	init_field_2d_float(zaz_j);
	init_field_2d_float(zag_i);
	init_field_2d_float(zag_j);

}

int* FlowField::mem_allocate_2d_int(){	

	return new int [(parameters_.get_num_cells(0)+2)*
					(parameters_.get_num_cells(1)+2)];

}

FLOAT* FlowField::mem_allocate_2d_float(){

	return new FLOAT [(parameters_.get_num_cells(0)+2)*
					  (parameters_.get_num_cells(1)+2)];
		
}

FLOAT* FlowField::mem_allocate_3d_float(){

	return new FLOAT [(parameters_.get_num_cells(0)+2)*
					  (parameters_.get_num_cells(1)+2)*
					   parameters_.get_num_cells(2)];

}

void FlowField::init_field_2d_int(int* field){
	#pragma omp parallel for schedule(static)
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j <parameters_.get_num_cells(1)+2	; j++) {
			field[map(i,j)]=0;
		}
	}

}

void FlowField::init_field_2d_float(FLOAT* field){

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j <parameters_.get_num_cells(1)+2	; j++) {
			field[map(i,j)]=0.0;
		}
	}

}

void FlowField::init_field_3d_float(FLOAT* field){

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for (int j = 0; j <parameters_.get_num_cells(1)+2	; j++) {
			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				field[map(i,j,k)]=0.0;
			}				
		}
	}

}


FlowField::~FlowField(){

	delete [] u;
	delete [] v;
	delete [] w;
	delete [] dz_i;
	delete [] dz_j;
	delete [] dz_k;
	delete [] g_i;
	delete [] g_j;
	delete [] g_k;
	
	delete [] m;
	delete [] M;

	delete [] delta;
	delete [] zaz_i;
	delete [] zaz_j;
	delete [] zag_i;
	delete [] zag_j;
}

void FlowField::printEtta(int it){

	std::cout << "water elevation at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << etta[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printm(int it){

	std::cout << "m at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << m[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printM(int it){

	std::cout << "M at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << M[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printDzI(int it){

	std::cout << "DzI at time step:" << it  << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << dz_i[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printDzJ(int it){

	std::cout << "DzJ at time step:" << it  << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << dz_j[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printDzK(int it){
								
	std::cout << "DzK at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << dz_k[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}
								
}

void FlowField::printU(int it){

	std::cout << "velocity; U: at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << u[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printV(int it){

	std::cout << "velocity; V: at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << v[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printW(int it){

	std::cout << "velocity; W: at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << w[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printGI(int it){

	std::cout << "GI at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << g_i[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printGJ(int it){

	std::cout << "GJ at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << g_j[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printGK(int it){

	std::cout << "GK at time step:" << it << std::endl;
	for(int k = 0; k < parameters_.get_num_cells(2); k++){
		std::cout << "layer: " << k << std::endl;
		for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
				if (k <= M[map(i,j)]-m[map(i,j)] ) {
				std::cout << g_k[map(i,j,k)] << "\t";
				}
				else{
				std::cout << "x" << "\t";
				}
			}
			std::cout << std::endl;
		}
	}

}

void FlowField::printZazi(int it){

	std::cout << " ZI' * inv AI * ZI at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << zaz_i[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printZazj(int it){

	std::cout << "ZJ' * inv AJ * ZJ at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << zaz_j[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printZagi(int it){

	std::cout << "ZI' * inv AI * GI at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << zag_i[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::printZagj(int it){

	std::cout << "ZJ' * inv AJ * GJat time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << zag_j[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}

void FlowField::PrintDelta(int it){

	std::cout << "test Delta at time step:" << it << std::endl;
	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
			std::cout << delta[map(i,j)] << "\t";
		}
		std::cout << std::endl;
	}

}
