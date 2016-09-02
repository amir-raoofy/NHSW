#include <Parameters.h>

class flowField
{
public:
	flowField(Parameters* parameters);
	~flowField();
	void init_data();
	void init_vel_field();
	void init_dz();
	void init_h();
	void init_m();
	void update_A();
	void update_M();
	// for debug only
	void print_data();
private:
	/* data */
	float * _u	;	// velocity field data
	float * _v	;
	float * _w	;

	float * _F	;	// intermediate clac. functions
	float * _G 	;

	float * _A 	;	// coeff. matrix for implicit solver for height for first step

	float * _dz	;	// data of delta_z of all cells
	float * _q	;	// data for non-hydro-static pressure
	float * _h	;	// height data
	int   * _m	;	// discretized bathymetry
	int   * _M	;	// discretized height of water

	Parameters * _parameters;
};
