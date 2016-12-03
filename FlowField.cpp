#include "FlowField.h"

FlowField::FlowField(const Parameters& parameters):
	parameters_(parameters),
	height_(	parameters_.GetHeight()),
	dz_i_	(		parameters_.get_num_cells(0),
						DiscreteRectangle( parameters_.get_num_cells(1))	),
	dz_j_	(		parameters_.get_num_cells(0),
						DiscreteRectangle( parameters_.get_num_cells(1))	),
	etta_	( 	parameters_.get_num_cells(0),
						DiscreteLine( parameters_.get_num_cells(1), 0.0)	),
	delta_( 	parameters_.get_num_cells(0),
						DiscreteLine( parameters_.get_num_cells(1), 0.0)	),
	m_ 		( 	parameters_.get_num_cells(0),
						LineFlagField(parameters_.get_num_cells(1), 0.0) 	),
	M_		( 	parameters_.get_num_cells(0),
						LineFlagField(parameters_.get_num_cells(1), 0.0) 	),
	u_boundaries_(6),
	v_boundaries_(6),
	w_boundaries_(6),
	g_i_boundaries_(6),
	g_j_boundaries_(6),
	dz_i_boundaries_(6),
	dz_j_boundaries_(6),
	q_boundaries_(6),
	etta_boundaries_(4){
		SetEttaBoundaries()[0] = DiscreteLine(parameters_.get_num_cells(1));
		SetEttaBoundaries()[1] = DiscreteLine(parameters_.get_num_cells(1));
		SetEttaBoundaries()[2] = DiscreteLine(parameters_.get_num_cells(0));
		SetEttaBoundaries()[3] = DiscreteLine(parameters_.get_num_cells(0));

//		TODO move to constructor
//		dz_i_(parameters_.get_num_cells(0));
//						DiscreteRectangle( parameters_.get_num_cells(1)));
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
//const DiscreteRectangle& FlowField::GetWaterSurface() const {return etta_;} //TODO later on add the value of h to get the total height
const RectangleFlagField& FlowField::Getm() const {return m_;}
const RectangleFlagField& FlowField::GetM() const {return M_;}
const DiscreteCube& FlowField::GetGI() const {return g_i_;}
const DiscreteCube& FlowField::GetGJ() const {return g_j_;}
const DiscreteCube& FlowField::GetDzI() const {return dz_i_;}
const DiscreteCube& FlowField::GetDzJ() const {return dz_j_;}
const DiscreteCube& FlowField::GetQ() const {return q_;}
const DiscreteCube& FlowField::GetU_boundaries() const{return u_boundaries_;}
const DiscreteCube& FlowField::GetV_boundaries() const{return v_boundaries_;}
const DiscreteCube& FlowField::GetW_boundaries() const{return w_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesGI() const{return g_i_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesGJ() const{return g_j_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesDzI() const{return dz_i_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesDzJ() const{return dz_j_boundaries_;}
const DiscreteCube& FlowField::GetBoundariesQ() const{return q_boundaries_;}
const DiscreteRectangle& FlowField::GetEttaBoundaries() const{return etta_boundaries_;}

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
void FlowField::SetU_boundaries(DiscreteCube u_boundaries){u_boundaries_ = u_boundaries;}
void FlowField::SetV_boundaries(DiscreteCube v_boundaries){v_boundaries_ = v_boundaries;}
void FlowField::SetW_boundaries(DiscreteCube w_boundaries){w_boundaries_ = w_boundaries;}
void FlowField::SetEttaBoundaries(DiscreteRectangle etta_boundaries){etta_boundaries_ = etta_boundaries;}
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
RectangleFlagField& FlowField::Setm() {return m_;}
RectangleFlagField& FlowField::SetM() {return M_;}
DiscreteCube& FlowField::SetGI() {return g_i_;}
DiscreteCube& FlowField::SetGJ() {return g_j_;}
DiscreteCube& FlowField::SetDzI() {return dz_i_;}
DiscreteCube& FlowField::SetDzJ() {return dz_j_;}
DiscreteCube& FlowField::SetQ() {return q_;}
DiscreteCube& FlowField::SetU_boundaries() {return u_boundaries_;}
DiscreteCube& FlowField::SetV_boundaries() {return v_boundaries_;}
DiscreteCube& FlowField::SetW_boundaries() {return w_boundaries_;}
DiscreteCube& FlowField::SetBoundariesGI() {return g_i_boundaries_;}
DiscreteCube& FlowField::SetBoundariesGJ() {return g_j_boundaries_;}
DiscreteCube& FlowField::SetBoundariesDzI() {return dz_i_boundaries_;}
DiscreteCube& FlowField::SetBoundariesDzJ() {return dz_j_boundaries_;}
DiscreteCube& FlowField::SetBoundariesQ() {return q_boundaries_;}
DiscreteRectangle& FlowField::SetEttaBoundaries() {return etta_boundaries_;}
