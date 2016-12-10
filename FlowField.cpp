#include "FlowField.h"

FlowField::FlowField(const Parameters& parameters):
	parameters_(parameters),
	height_(	parameters_.GetHeight()),
	u_	(			parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	v_	(			parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	w_	(			parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	g_i_	(		parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	g_j_	(		parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	dz_i_	(		parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	dz_j_	(		parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	q_	(			parameters_.get_num_cells(0)+2,
						DiscreteRectangle( parameters_.get_num_cells(1)+2)	),
	etta_	( 	parameters_.get_num_cells(0)+2,
						DiscreteLine( parameters_.get_num_cells(1)+2, 0.0)	),
	delta_( 	parameters_.get_num_cells(0)+2,
						DiscreteLine( parameters_.get_num_cells(1)+2, 0.0)	),
	zaz_i_( 	parameters_.get_num_cells(0)+2,
						DiscreteLine( parameters_.get_num_cells(1)+2, 0.0)	),
	zaz_j_( 	parameters_.get_num_cells(0)+2,
						DiscreteLine( parameters_.get_num_cells(1)+2, 0.0)	),
	m_ 		( 	parameters_.get_num_cells(0)+2,
						LineFlagField(parameters_.get_num_cells(1)+2, 0.0) 	),
	M_		( 	parameters_.get_num_cells(0)+2,
						LineFlagField(parameters_.get_num_cells(1)+2, 0.0) 	),
	u_boundaries_(6),
	v_boundaries_(6),
	w_boundaries_(6),
	g_i_boundaries_(6),
	g_j_boundaries_(6),
	dz_i_boundaries_(6),
	dz_j_boundaries_(6),
	q_boundaries_(6),
	etta_boundaries_(4){
		SetBoundariesEtta()[0] = DiscreteLine(parameters_.get_num_cells(1));
		SetBoundariesEtta()[1] = DiscreteLine(parameters_.get_num_cells(1));
		SetBoundariesEtta()[2] = DiscreteLine(parameters_.get_num_cells(0));
		SetBoundariesEtta()[3] = DiscreteLine(parameters_.get_num_cells(0));
	}

FlowField::~FlowField(){}

void FlowField::PrintData(int it){it++;// jsut to get rid of the error
} //TODO re-implement the print function

//implmentation of getters
const DiscreteCube& FlowField::GetU() const {return u_;}
const DiscreteCube& FlowField::GetV() const {return v_;}
const DiscreteCube& FlowField::GetW() const {return w_;}
const DiscreteRectangle& FlowField::GetEtta() const { return etta_;}
const DiscreteRectangle& FlowField::GetDelta() const { return etta_;}
const DiscreteRectangle& FlowField::GetZazI() const { return zaz_i_;}
const DiscreteRectangle& FlowField::GetZazJ() const { return zaz_j_;}
//const DiscreteRectangle& FlowField::GetWaterSurface() const {return etta_;} //TODO later on add the value of h to get the total height
const RectangleFlagField& FlowField::Getm() const {return m_;}
const RectangleFlagField& FlowField::GetM() const {return M_;}
const DiscreteCube& FlowField::GetGI() const {return g_i_;}
const DiscreteCube& FlowField::GetGJ() const {return g_j_;}
const DiscreteCube& FlowField::GetDzI() const {return dz_i_;}
const DiscreteCube& FlowField::GetDzJ() const {return dz_j_;}
const DiscreteCube& FlowField::GetQ() const {return q_;}
const DiscreteCube& FlowField::GetBoundariesU() const{return u_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesV() const{return v_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesW() const{return w_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesGI() const{return g_i_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesGJ() const{return g_j_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesDzI() const{return dz_i_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesDzJ() const{return dz_j_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesQ() const{return q_boundaries_;}
const DiscreteRectangle& FlowField::GetBoundariesEtta() const{return etta_boundaries_;}

//DONE setters implementation
void FlowField::SetU(DiscreteCube& u){u_=u;}
void FlowField::SetV(DiscreteCube& v){v_=v;}
void FlowField::SetW(DiscreteCube& w){w_=w;}
void FlowField::SetEtta(DiscreteRectangle& etta){etta_=etta;}
void FlowField::SetDelta(DiscreteRectangle& delta){delta_=delta;}
void FlowField::Setm(RectangleFlagField& m){m_=m;}
void FlowField::SetM(RectangleFlagField& M){M_=M;}
void FlowField::SetGI(DiscreteCube& g_i){g_i_=g_i;}
void FlowField::SetGJ(DiscreteCube& g_j){g_j_=g_j;}
void FlowField::SetDzI(DiscreteCube& dz_i){dz_i_=dz_i;}
void FlowField::SetDzJ(DiscreteCube& dz_j){dz_j_=dz_j;}
void FlowField::SetQ(DiscreteCube& q){q_=q;}
void FlowField::SetBoundariesU(DiscreteCube u_boundaries){u_boundaries_ = u_boundaries;}
void FlowField::SetBoundariesV(DiscreteCube v_boundaries){v_boundaries_ = v_boundaries;}
void FlowField::SetBoundariesW(DiscreteCube w_boundaries){w_boundaries_ = w_boundaries;}
void FlowField::SetBoundariesEtta(DiscreteRectangle etta_boundaries){etta_boundaries_ = etta_boundaries;}
void FlowField::SetBoundariesGI(DiscreteCube g_i_boundaries){g_i_boundaries_ = g_i_boundaries;}
void FlowField::SetBoundariesGJ(DiscreteCube g_j_boundaries){g_j_boundaries_ = g_j_boundaries;}
void FlowField::SetBoundariesDzI(DiscreteCube dz_i_boundaries){dz_i_boundaries_ = dz_i_boundaries;}
void FlowField::SetBoundariesDzJ(DiscreteCube dz_j_boundaries){dz_j_boundaries_ = dz_j_boundaries;}
void FlowField::SetBoundariesQ(DiscreteCube q_boundaries){q_boundaries_ = q_boundaries;}
//overloaded setters
DiscreteCube& FlowField::SetU() {return u_;}
DiscreteCube& FlowField::SetV() {return v_;}
DiscreteCube& FlowField::SetW() {return w_;}
DiscreteRectangle& FlowField::SetEtta() { return etta_;}
DiscreteRectangle& FlowField::SetDelta() { return etta_;}
DiscreteRectangle& FlowField::SetZazI() {return zaz_i_;}
DiscreteRectangle& FlowField::SetZazJ() {return zaz_j_;}
RectangleFlagField& FlowField::Setm() {return m_;}
RectangleFlagField& FlowField::SetM() {return M_;}
DiscreteCube& FlowField::SetGI() {return g_i_;}
DiscreteCube& FlowField::SetGJ() {return g_j_;}
DiscreteCube& FlowField::SetDzI() {return dz_i_;}
DiscreteCube& FlowField::SetDzJ() {return dz_j_;}
DiscreteCube& FlowField::SetQ() {return q_;}
DiscreteCube& FlowField::SetBoundariesU() {return u_boundaries_;}
DiscreteCube& FlowField::SetBoundariesV() {return v_boundaries_;}
DiscreteCube& FlowField::SetBoundariesW() {return w_boundaries_;}
DiscreteCube& FlowField::SetBoundariesGI() {return g_i_boundaries_;}
DiscreteCube& FlowField::SetBoundariesGJ() {return g_j_boundaries_;}
DiscreteCube& FlowField::SetBoundariesDzI() {return dz_i_boundaries_;}
DiscreteCube& FlowField::SetBoundariesDzJ() {return dz_j_boundaries_;}
DiscreteCube& FlowField::SetBoundariesQ() {return q_boundaries_;}
DiscreteRectangle& FlowField::SetBoundariesEtta() {return etta_boundaries_;}
