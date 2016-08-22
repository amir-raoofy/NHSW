#include <Parameters.h>

class flowField
{
public:
	flowField(Parameters* parameters);
	~flowField();
	void init_vel_field();
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

	Parameters * _parameters;
};
