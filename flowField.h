#include <Parameters.h>
#include <solver.h>
#include <helper.h>

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
	void update_F();
	void update_F_boundary();
	void update_G();
	void update_G_boundary();
	void update_S();
	void update_T();
	void update_h();
	void update_u_v();
	void update_P();
	void update_R();
	void solve_q();
	void update_u_v_w();
	void solve_h();
// for debug only
	void print_data(int it);
	void test_solver();

	//methods
	int map(int i, int j) const;
	int map2d(int i, int j) const;
	int map(int i, int j, int k) const;
	int map3d(int i, int j) const;
	int map(int i, int j, int k, int l) const;

	float* get_u() const;
	float* get_v() const;
	float* get_w() const;
	float* get_height() const;
	int* get_m() const;
	float* get_DZ() const;
	float* get_q() const;

	private:
	/* data */
	float * _u	;	// velocity field data
	float * _v	;
	float * _w	;

	float * _F	;	// intermediate clac. functions
	float * _G 	;

	float * _A 	;	// coeff. matrix for linear solver for height for first step
	float * _S;   // coeff. matrix for implicit solver for height
	float * _T;   // right hand_side for implicit solver for height
	float * _P;   // coeff. matrix for implicit solver for hydrodynamic pressure
	float * _R;   // right hand_side for implicit solver for hydrodynamic pressure

	float * _dz	;	// data of delta_z of all cells
	float * _q	;	// data for non-hydro-static pressure
	float * _h	;	// height data
	int   * _m	;	// discretized bathymetry
	int   * _M	;	// discretized height of water

	Parameters * _parameters;


};
