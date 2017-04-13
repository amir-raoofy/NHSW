#include "Simulation.h"
#include <numeric>

void Simulation::CalculateDelta(){

	FLOAT s1=0.0,s2=0.0,s3=0.0,s4=0.0;
	// Domain
	for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			
			s1=0.0;s2=0.0;s3=0.0,s4=0.0;

			for (int k = 0; k < parameters_.get_num_cells(2); k++) {
				s1+=flowField_.dz_i[map(i,j  ,k)] * flowField_.u[map(i,j  ,k)];
				s2+=flowField_.dz_i[map(i-1,j,k)] * flowField_.u[map(i-1,j,k)];
				s3+=flowField_.dz_j[map(i,j  ,k)] * flowField_.v[map(i,j  ,k)];
				s4+=flowField_.dz_j[map(i,j-1,k)] * flowField_.v[map(i,j-1,k)];
			}

			s1*=(1-parameters_.get_theta()) * time_step / parameters_.get_dxdydz(0);
			s2*=(1-parameters_.get_theta()) * time_step / parameters_.get_dxdydz(0);
			s3*=(1-parameters_.get_theta()) * time_step / parameters_.get_dxdydz(1);
			s4*=(1-parameters_.get_theta()) * time_step / parameters_.get_dxdydz(1);
			
			flowField_.delta[map(i,j)] = flowField_.etta[map(i,j)]-(s1-s2+s3-s4) ;
			// rain fall	
			flowField_.delta[map(i,j)] += parameters_.GetPrecipitation() * time_step ;
			
				
		}
	}

}
