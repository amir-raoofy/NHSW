#pragma once
#include "Parameters.h"
#include "data_structure.h"

/* @class FlowField
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
	void PrintData(int it=0);

	// methods	
	// getters
	const	DiscreteCube& GetU() const;
	const DiscreteCube& GetV() const;
	const DiscreteCube& GetW() const;
	const DiscreteRectangle& GetEtta() const;
	const DiscreteRectangle& GetDelta() const;
	const DiscreteRectangle& GetZazI() const;
	const DiscreteRectangle& GetZazJ() const;
	const DiscreteRectangle& GetWaterSurface() const;
	const RectangleFlagField& Getm() const;
	const RectangleFlagField& GetM() const;
	const DiscreteCube& GetGI() const;
	const DiscreteCube& GetGJ() const;
	const DiscreteCube& GetDzI() const;
	const DiscreteCube& GetDzJ() const;
	const DiscreteCube& GetQ() const;

	const DiscreteCube& GetBoundariesU() const;
	const DiscreteCube& GetBoundariesV() const;
	const DiscreteCube& GetBoundariesW() const;
	const DiscreteRectangle& GetBoundariesEtta() const;
	const DiscreteCube& GetBoundariesGI() const;
	const DiscreteCube& GetBoundariesGJ() const;
	const DiscreteCube& GetBoundariesDzI() const;
	const DiscreteCube& GetBoundariesDzJ() const;
	const DiscreteCube& GetBoundariesQ() const;

	//DONE declare setters
	void SetU(DiscreteCube& u);
	void SetV(DiscreteCube& v);
	void SetW(DiscreteCube& w);
	void SetEtta(DiscreteRectangle& etta);
	void SetDelta(DiscreteRectangle& delta);
	void Setm(RectangleFlagField& m);
	void SetM(RectangleFlagField& M);
	void SetGI(DiscreteCube& g_i);
	void SetGJ(DiscreteCube& g_j);
	void SetDzI(DiscreteCube& dz_i);
	void SetDzJ(DiscreteCube& dz_j);
	void SetQ(DiscreteCube& q);

	void SetBoundariesU(DiscreteCube u_boundaries);
	void SetBoundariesV(DiscreteCube v_boundaries);
	void SetBoundariesW(DiscreteCube w_boundaries);
	void SetBoundariesEtta(DiscreteRectangle etta_boundaries);
	void SetBoundariesGI(DiscreteCube g_i_boundaries);
	void SetBoundariesGJ(DiscreteCube g_j_boundaries);
	void SetBoundariesDzI(DiscreteCube dz_i_boundaries);
	void SetBoundariesDzJ(DiscreteCube dz_j_boundaries);
	void SetBoundariesQ(DiscreteCube q_boundaries);
	//overloadted setters
	DiscreteCube& SetU();
	DiscreteCube& SetV();
	DiscreteCube& SetW();
	DiscreteRectangle& SetEtta();
	DiscreteRectangle& SetDelta();
	DiscreteRectangle& SetZazI();
	DiscreteRectangle& SetZazJ();
	RectangleFlagField& Setm();
	RectangleFlagField& SetM();
	DiscreteCube& SetGI();
	DiscreteCube& SetGJ();
	DiscreteCube& SetDzI();
	DiscreteCube& SetDzJ();
	DiscreteCube& SetQ();

	DiscreteCube& SetBoundariesU();
	DiscreteCube& SetBoundariesV();
	DiscreteCube& SetBoundariesW();
	DiscreteRectangle& SetBoundariesEtta();
	DiscreteCube& SetBoundariesGI();
	DiscreteCube& SetBoundariesGJ();
	DiscreteCube& SetBoundariesDzI();
	DiscreteCube& SetBoundariesDzJ();
	DiscreteCube& SetBoundariesQ();
	
private:
	const Parameters& parameters_; 										//reference to the parameters
	const float height_	;															// reference height of water

	/*domain data */
	// velocity
	DiscreteCube u_; 																	// velocity field data domain
	DiscreteCube v_;
	DiscreteCube w_;

	// g_ij
	DiscreteCube g_i_;																// intermediate clac. functions
	DiscreteCube g_j_;
	
	// dz
	DiscreteCube dz_i_;																// data of delta_z of all cells
	DiscreteCube dz_j_;

	// non hydrostatic pressure
	DiscreteCube q_;																	// data for non-hydro-static pressure

	// elevation
	DiscreteRectangle etta_;													// free surface heaight elevation

	// intermediate buffer for elevation
	DiscreteRectangle delta_;													// intermediate buffer
	DiscreteRectangle zaz_i_;													// intermediate buffer
	DiscreteRectangle zaz_j_;													// intermediate buffer

	// higher and lower indices for 3rd dimension iteration
	RectangleFlagField m_	;														// discretized bathymetry
	RectangleFlagField M_	;														// discretized height of water

	/* boundary data */
	// velocity boundaries
	DiscreteCube u_boundaries_;												// u boundaries
	DiscreteCube v_boundaries_;												// v boundaries
	DiscreteCube w_boundaries_;												// w boundaries

	// g_ij boundaries
	DiscreteCube g_i_boundaries_;											// boundaries for g_i
	DiscreteCube g_j_boundaries_;											// boundaries for g_j

	// boundaries for dz
	DiscreteCube dz_i_boundaries_;											// boundaries for dz_i
	DiscreteCube dz_j_boundaries_;											// boundaries for dz_j

	// boundaries for q
	DiscreteCube q_boundaries_;												// boundaries for non hydrostatic pressure

	// boundaries for etta
	DiscreteRectangle etta_boundaries_; 								// boundaries for surface elevation
};
