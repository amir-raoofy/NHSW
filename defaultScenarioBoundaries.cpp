#include "defaultScenario.h"

void defaultScenario::updateBoundariesDzI(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(0,j,k)]=flowField_.dz_i[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_i[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,0,k)]=flowField_.dz_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_i[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}

void defaultScenario::updateBoundariesDzJ(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(0,j,k)]=flowField_.dz_j[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_j[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,0,k)]=flowField_.dz_j[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_j[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_j[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}

void defaultScenario::updateBoundariesDzK(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(0,j,k)]=flowField_.dz_k[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.dz_k[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,0,k)]=flowField_.dz_k[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.dz_k[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.dz_k[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}

void defaultScenario::updateBoundariesGI(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(0,j,k)]=0.0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(parameters_.get_num_cells(0)+1,j,k)]=0.0;
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,0,k)]=flowField_.g_i[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_i[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_i[map(i,parameters_.get_num_cells(1),k)];
		}
	}
	
}

void defaultScenario::updateBoundariesGJ(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_j[map(0,j,k)]=flowField_.g_j[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_j[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_j[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_j[map(i,0,k)]=flowField_.g_j[map(i,1,k)];
			flowField_.g_j[map(i,0,k)]=0.0;
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			//flowField_.g_j[i][parameters_.get_num_cells(0)+1][k]=flowField_.g_j[i][parameters_.get_num_cells(0)][k];
			flowField_.g_j[map(i,parameters_.get_num_cells(1)+1,k)]=0.0;
			//flowField_.g_j[i][parameters_.get_num_cells(1)  ][k]=0.0;
		}
	}

}

void defaultScenario::updateBoundariesGK(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(0,j,k)]=flowField_.g_k[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.g_k[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(i,0,k)]=flowField_.g_k[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.g_k[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.g_k[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}

void defaultScenario::updateBoundariesZAZI(){}
void defaultScenario::updateBoundariesZAZJ(){}
void defaultScenario::updateBoundariesZAGI(){}
void defaultScenario::updateBoundariesZAGJ(){}
void defaultScenario::updateBoundariesDelta(){}

void defaultScenario::updateBoundariesEtta(){

	for (int j = 0; j < parameters_.get_num_cells(1)+2; j++) {
		flowField_.etta[map(0,j)]=flowField_.etta[map(1,j)];								//left
		flowField_.etta[map(parameters_.get_num_cells(0)+1,j)]=flowField_.etta[map(parameters_.get_num_cells(0),j)];	//right
	}
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		flowField_.etta[map(i,0)]=flowField_.etta[map(i,1)];								//back
		flowField_.etta[map(i,parameters_.get_num_cells(1)+1)]=flowField_.etta[map(i,parameters_.get_num_cells(1))];	//front
	}

}

void defaultScenario::updateBoundariesU(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.u[map(0,j,k)]=0;
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.u[map(parameters_.get_num_cells(0)+1,j,k)]=0;
		}
	}
	//back
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.u[map(i,0,k)]=flowField_.u[map(i,1,k)];
		}
	}
	//front
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.u[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.u[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}
void defaultScenario::updateBoundariesV(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(0,j,k)]=flowField_.v[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.v[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//back
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(i,0,k)]=0;
		}
	}
	//front
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.v[map(i,parameters_.get_num_cells(1)+1,k)]=0;
		}
	}

}

void defaultScenario::updateBoundariesW(){

	//left
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(0,j,k)]=flowField_.w[map(1,j,k)];
		}
	}
	//right
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(parameters_.get_num_cells(0)+1,j,k)]=flowField_.w[map(parameters_.get_num_cells(0),j,k)];
		}
	}
	//bottom
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(i,0,k)]=flowField_.w[map(i,1,k)];
		}
	}
	//top
	for (int i = 0; i < parameters_.get_num_cells(0)+2; i++) {
		for(int k = 0; k < parameters_.get_num_cells(2); k++){
			flowField_.w[map(i,parameters_.get_num_cells(1)+1,k)]=flowField_.w[map(i,parameters_.get_num_cells(1),k)];
		}
	}

}

