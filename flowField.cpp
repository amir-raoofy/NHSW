#include <flowField.h>

//default constructor // Nx=Ny=Nz=10
flowField::flowField(Parameters* parameters):
	_parameters(parameters){

	// memory allocation
	_u = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_v = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_w = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_F = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_G = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_A = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)*
					(_parameters->get_num_cells(2)+2)];
	_S = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)];
	_T = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)];
	_dz= new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_P = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)*
					(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_R = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_q = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_h = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)];
	_m = new int   [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)];
	_M = new int   [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)];
}

flowField::~flowField(){
	delete[] _u	;
	delete[] _v	;
	delete[] _w	;
	delete[] _F	;
	delete[] _G	;
	delete[] _A	;
	delete[] _S ;
	delete[] _T ;
	delete[] _dz;
	delete[] _q	;
	delete[] _h	;
	delete[] _m	;
	delete[] _M	;
}

void flowField::init_data(){
	for (int i = 0; i < (_parameters->get_num_cells(0)+2) *
				   		(_parameters->get_num_cells(1)+2) *
						(_parameters->get_num_cells(2)+2) 
						; i++){
		_u	[i] = 0.0;
		_v	[i] = 0.0;
		_w	[i] = 0.0;
		_F	[i] = 0.0;
		_G	[i] = 0.0;
		_dz	[i] = 0.0;
		_q	[i] = 0.0;
		_R	[i] = 0.0;
	}

	for (int i = 0; i < (_parameters->get_num_cells(0)+2) *
				   		(_parameters->get_num_cells(1)+2) *
						(_parameters->get_num_cells(2)+2) * 
						(_parameters->get_num_cells(2)+2) 
						; i++){
		_A	[i] = 0.0;
	}

	for (int i = 0; i < (_parameters->get_num_cells(0)+2) *
				   		(_parameters->get_num_cells(1)+2)
						; i++){
		_h	[i] = 0.0;
		_m	[i] = 0;
		_M	[i] = 0;
		_T	[i] = 0.0;
	}


	for (int i = 0; i <  (_parameters->get_num_cells(0)+2) *
						 (_parameters->get_num_cells(1)+2) *
					  	 (_parameters->get_num_cells(0)+2) *
					   	 (_parameters->get_num_cells(1)+2)
	   					 ; i++	)
		_S  [i] = 0.0;

	for (int i = 0; i <  (_parameters->get_num_cells(0)+2) *
						 (_parameters->get_num_cells(1)+2) *
					  	 (_parameters->get_num_cells(2)+2) *
					  	 (_parameters->get_num_cells(0)+2) *
					  	 (_parameters->get_num_cells(1)+2) *
					   	 (_parameters->get_num_cells(2)+2)
	   					 ; i++	)
		_P  [i] = 0.0;

}

void flowField::init_vel_field(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_u	[ map(i,j,k) ] = 0.0;
				_v	[ map(i,j,k) ] = 0.0;
				_w	[ map(i,j,k) ] = 0.0;
			}
		}
	}
}

void flowField::init_dz(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_dz	[ map(i,j,k) ] = _parameters->get_dxdydz(2);
			}
		}
	}
}

void flowField::init_h(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
/*				_h	[ map(i,j) ] 	= _parameters->get_num_cells(2)
							  		* _parameters->get_dxdydz(2) 
								  	/ 2.0
							  		+ (i)
							 		*	(_parameters->get_num_cells(0))
							  		* _parameters->get_dxdydz(0) 
							  		/ 40.0 ;
*/
//				_h	[ map(i,j) ] 	= (i < (_parameters->get_num_cells(0)+2)/2)? _parameters->get_num_cells(2)*_parameters->get_dxdydz(2)/2:_parameters->get_num_cells(2)*_parameters->get_dxdydz(2) ;
				_h	[ map(i,j) ] 	= (i < (_parameters->get_num_cells(0)+2)/2)? _parameters->get_num_cells(2)*_parameters->get_dxdydz(2)/2:_parameters->get_num_cells(2)*_parameters->get_dxdydz(2)/2+2.0 ;
		}
	}
}


void flowField::init_m(){
	for (int i = 0; i < (_parameters->get_num_cells(0)+2) *
				   		(_parameters->get_num_cells(1)+2)
						; i++){
		_m	[i] = 1;
	}

}

void flowField::update_M(){

	for (int i = 0; i < (_parameters->get_num_cells(0)+2)*
						(_parameters->get_num_cells(1)+2)
					; i++) {
		_M[i] = ceil(_h[i]/ _parameters->get_dxdydz(2));
	}
}

void flowField::update_A(){

	float alpha = _parameters->get_vis() * _parameters->get_sim_time() / _parameters->get_dxdydz(2);
	
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_A	[ map(i,j,k,k) ] = 1.0;
			}
			for (int k =  _m [ map(i,j) ]; k <= _M	[ map(i,j) ];	 k++) {
				_A	[ map(i,j,k,k)]	= 2* alpha + _dz	[map (i,j,k) ];
				if (k!=(_parameters->get_num_cells(2)+1)) 
					_A	[ map(i,j,k,k+1) ] =  -alpha;
				if (k!=0)
					_A	[ map(i,j,k,k-1) ] =  -alpha;
			}

			int k =  _m	[ map(i,j) ];
			_A [ map(i,j,k,k) ]	+=  _parameters->get_gamma_b() * _parameters->get_sim_time();
			k = _M[ map(i,j) ];
			_A [ map(i,j,k,k) ] +=  _parameters->get_gamma_t() * _parameters->get_sim_time();

		}
	}
}

void flowField::update_S(){
	float TOL = 0.0001;
	int MAXIT = 1000000;
	float * x = new float [_parameters->get_num_cells(2)+2];
	for (int i = 0; i < _parameters->get_num_cells(2)+2 ; i++) {
		x[i]=1;
	}

	Jacobi *solver = new Jacobi(_A, _dz, x, _parameters->get_num_cells(2)+2);

	float alpha =
	_parameters->get_g() 
	 * (_parameters->get_theta()   * _parameters->get_theta()  )
	 * (_parameters->get_time_step()      * _parameters->get_time_step()     )
	 / (_parameters->get_dxdydz(0) * _parameters->get_dxdydz(0));

	float beta =
	_parameters->get_g() 
	 * (_parameters->get_theta()   * _parameters->get_theta()  )
	 * (_parameters->get_time_step()      * _parameters->get_time_step()     )
	 / (_parameters->get_dxdydz(1) * _parameters->get_dxdydz(1));

	//initialize the coeff matrix
	for (int i = 0; i <  (_parameters->get_num_cells(0)+2) *
					 (_parameters->get_num_cells(1)+2) *
				  	 (_parameters->get_num_cells(0)+2) *
				   	 (_parameters->get_num_cells(1)+2)
   					 ; i++	)
		_S  [i] = 0.0;
	
	//set the domain coeffs
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
				_S	[map2d(map(i,j) , map(i,j))] = +1; 					//set the coefficient for all the domain and boundary to 1 
		}
	}

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			solver->set_A_and_b(_A+map(i,j,0,0),_dz+map(i,j,0));
			solver->solve(TOL, MAXIT);
				_S	[map2d(map(i,j) , map(i,j))]
					+= + alpha * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2)		// alpha _ i _ j
					   + beta  * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2);	// beta  _ i _ j
				_S	[map2d(map(i,j) , map(i,j)+1)]
					-= alpha * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2);		// -alpha _ i _ j
				_S	[map2d(map(i,j), map(i,j)+(_parameters->get_num_cells(0)+2))]
					-= beta  * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2);		// -beta _ i _ j

			solver->set_A_and_b(_A+map(i-1,j,0,0),_dz+map(i-1,j,0));
			solver->solve(TOL, MAXIT);
				_S	[map2d(map(i,j) , map(i,j))]
					+= alpha * dot_product(_dz+map(i-1,j,0), x, _parameters->get_num_cells(2)+2);		// alpha _ i-1 _ j
				_S	[map2d(map(i,j) , map(i,j)-1)]
					-= alpha * dot_product(_dz+map(i-1,j,0), x, _parameters->get_num_cells(2)+2);		// -alpha _ i-1 _ j

			solver->set_A_and_b(_A+map(i,j-1,0,0),_dz+map(i,j-1,0));
			solver->solve(TOL, MAXIT);
				_S	[map2d(map(i,j) , map(i,j))]
					+= beta * dot_product(_dz+map(i,j-1,0), x, _parameters->get_num_cells(2)+2);		// beta _ i _ j-1
				_S	[map2d(map(i,j) , map(i,j)-(_parameters->get_num_cells(0)+2))]	// -beta _ i _ j-1
					-= beta * dot_product(_dz+map(i,j-1,0), x, _parameters->get_num_cells(2)+2);

		}
	}
	//set the boundary coeffs
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		_S	[map2d(i, i+ _parameters->get_num_cells(0)+2)] = -1;
		_S	[map2d(i+ (_parameters->get_num_cells(0)+2)*
					  (_parameters->get_num_cells(1)+1)
				  ,i+ (_parameters->get_num_cells(0)+2)*
					  (_parameters->get_num_cells(1)+0))] = -1;
	}

	for (int j = 0; j <(_parameters->get_num_cells(0)+2)*
						(_parameters->get_num_cells(1)+2);
					j+= (_parameters->get_num_cells(0)+2)) {
		_S	[map2d(j, j+1)] = -1;
		_S	[map2d(j+_parameters->get_num_cells(0)+2 -1,
				   j+_parameters->get_num_cells(0)+2 -2)] = -1;
	}

	delete solver;
	delete [] x;
}

void flowField::update_T(){

	float TOL = 0.0001;
	int MAXIT = 1000000;
	float * x = new float [_parameters->get_num_cells(2)+2];
	for (int i = 0; i < _parameters->get_num_cells(2)+2 ; i++) {
		x[i]=1;
	}

	Jacobi *solver = new Jacobi(_A, _F, x, _parameters->get_num_cells(2)+2);

	float kappa =
		_parameters->get_theta()
	 * ( _parameters->get_time_step() )
	 / (_parameters->get_dxdydz(0) );

	float lambda =
		_parameters->get_theta()
	 * ( _parameters->get_time_step() )
	 / (_parameters->get_dxdydz(1) );

	float zeta =
	   ( 1 - _parameters->get_theta() )
	 * ( _parameters->get_time_step() )
	 / (_parameters->get_dxdydz(0) );
 
	float eta  =
	   ( 1 - _parameters->get_theta() )
	 * ( _parameters->get_time_step() )
	 / (_parameters->get_dxdydz(1) );



	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			_T [map(i,j)] =	_h [map(i,j)]
					  -	zeta * ( dot_product (_dz+map(i,j,0), _u+map(i,j,0), _parameters->get_num_cells(2)+2) 
									  - dot_product (_dz+map(i-1,j,0), _u+map(i-1,j,0), _parameters->get_num_cells(2)+2) )
					  -	eta  * ( dot_product (_dz+map(i,j,0), _v+map(i,j,0), _parameters->get_num_cells(2)+2) 
									  - dot_product (_dz+map(i,j-1,0), _v+map(i,j-1,0), _parameters->get_num_cells(2)+2) );
			solver->set_A_and_b(_A+map(i,j,0,0),_F+map(i,j,0));
			solver->solve(TOL, MAXIT);
			_T [map(i,j)] -= kappa * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2);		// kappa _ i _ j

			solver->set_A_and_b(_A+map(i-1,j,0,0),_F+map(i-1,j,0));
			solver->solve(TOL, MAXIT);
			_T [map(i,j)] += kappa * dot_product(_dz+map(i-1,j,0), x, _parameters->get_num_cells(2)+2);	// kappa _ i-1 _ j

			solver->set_A_and_b(_A+map(i,j,0,0),_G+map(i,j,0));
			solver->solve(TOL, MAXIT);
			_T [map(i,j)] -= lambda * dot_product(_dz+map(i,j,0), x, _parameters->get_num_cells(2)+2);		// lambda _ i _ j

			solver->set_A_and_b(_A+map(i,j-1,0,0),_G+map(i,j-1,0));
			solver->solve(TOL, MAXIT);
			_T [map(i,j)] += lambda * dot_product(_dz+map(i,j-1,0), x, _parameters->get_num_cells(2)+2);	// lambda _ i _ j-1
		}
	}

	//set the boundary coeffs
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		_T [map(i,0)] = 0;
		_T [map(i,_parameters->get_num_cells(1)+1)] = 0;
	}

	for (int j = 0; j <(_parameters->get_num_cells(1)+2); j++) {
		_T [map(0,j)] = 0;
		_T [map(_parameters->get_num_cells(0)+1,j)] = 0;
	}

	delete solver;
	delete [] x;
}

void flowField::update_h(){
	float TOL = 0.0001;
	int MAXIT = 1000000;

	Jacobi *solver = new Jacobi(_S, _T, _h, 
								(_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2));
	solver->solve(TOL, MAXIT);
	delete solver;
}

void flowField::update_F(){
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			for (int k =  _m [ map(i,j) ]; k <= _M	[ map(i,j) ];	 k++) {
				_F[ map(i,j,k) ]= _dz[map(i,j,k)] *
								( _u [ map(i,j,k) ] * (_u[ map(i,j,k) ] - _u [ map(i-1,j,k) ]) / _parameters->get_dxdydz(0)
								+ _v [ map(i,j,k) ] * (_u[ map(i,j,k) ] - _u [ map(i,j-1,k) ]) / _parameters->get_dxdydz(1)
								+ _w [ map(i,j,k) ] * (_u[ map(i,j,k) ] - _u [ map(i,j,k-1) ]) / _parameters->get_dxdydz(2)

								+ _parameters->get_viscosity()*(( _u [ map(i+1,j,k) ] - 2* _u[ map(i,j,k) ] + _u [map(i-1,j,k)])
											   	/ _parameters->get_dxdydz(0) * _parameters->get_dxdydz(0))
								+ _parameters->get_viscosity()*(( _u [ map(i,j+1,k) ] - 2* _u[ map(i,j,k) ] + _u [map(i,j-1,k)])
											   	/ _parameters->get_dxdydz(1) * _parameters->get_dxdydz(1))
								
								- ( 1-_parameters->get_theta() ) * _parameters->get_time_step()/_parameters->get_dxdydz(0) * 
								(_parameters->get_g()*(_h[map(i+1,j)]-_h[map(i,j)]) + _q[map(i+1,j,k)] - _q[map(i,j,k)]) );
			}
			int k =  _M	[ map(i,j) ];
			_F [ map(i,j,k) ] +=  _parameters->get_gamma_t() * _parameters->get_sim_time() * _parameters->get_u_a() ;
		}
	}
}

void flowField::update_G(){
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			for (int k =  _m [ map(i,j) ]; k <= _M	[ map(i,j) ];	 k++) {
				_G[ map(i,j,k) ]= _dz[map(i,j,k)] *
								( _u [ map(i,j,k) ] * (_v[ map(i,j,k) ] - _v [ map(i-1,j,k) ]) / _parameters->get_dxdydz(0)
								+ _v [ map(i,j,k) ] * (_v[ map(i,j,k) ] - _v [ map(i,j-1,k) ]) / _parameters->get_dxdydz(1)
								+ _w [ map(i,j,k) ] * (_v[ map(i,j,k) ] - _v [ map(i,j,k-1) ]) / _parameters->get_dxdydz(2)

								+ _parameters->get_viscosity()*(( _v [ map(i+1,j,k) ] - 2* _v[ map(i,j,k) ] + _v [map(i-1,j,k)])
											   	/ _parameters->get_dxdydz(0) * _parameters->get_dxdydz(0))
								+ _parameters->get_viscosity()*(( _v [ map(i,j+1,k) ] - 2* _v[ map(i,j,k) ] + _v [map(i,j-1,k)])
											   	/ _parameters->get_dxdydz(1) * _parameters->get_dxdydz(1))
								
								- ( 1-_parameters->get_theta() ) * _parameters->get_time_step()/_parameters->get_dxdydz(1) * 
								(_parameters->get_g()*(_h[map(i,j+1)]-_h[map(i,j)]) + _q[map(i,j+1,k)] - _q[map(i,j,k)]) );
			}
			int k =  _M	[ map(i,j) ];
			_G [ map(i,j,k) ] +=  _parameters->get_gamma_t() * _parameters->get_sim_time() * _parameters->get_v_a() ;
		}
	}
}

void flowField::update_u_v(){

	float TOL = 0.0001;
	int MAXIT = 1000000;
	float * x = new float [_parameters->get_num_cells(2)+2];
	float * b = new float [_parameters->get_num_cells(2)+2];

	for (int i = 0; i < _parameters->get_num_cells(2)+2 ; i++) {
		x[i]=1;
	}
	Jacobi *solver = new Jacobi(_A, b, x, _parameters->get_num_cells(2)+2);

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {

			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
			b[k]=0;
			}

			for (int k =  _m [ map(i,j) ]; k <= _M	[ map(i,j) ];	 k++) {
				b[k]=_F[map(i,j,k)] - _parameters->get_g()* _parameters->get_theta() * _parameters -> get_time_step()/_parameters->get_dxdydz(0) * ( _h [map(i+1,j)] - _h [map(i,j)] ) * _dz[map(i,j,k)];
			}
			solver->set_A_and_b(_A+map(i,j,0,0),b);
			solver->solve(TOL, MAXIT);

			for (int k = 0; k < _parameters->get_num_cells(2)+2 ; k++) {
				_u[map(i,j,k)]=x[k];
			}

			for (int k =  _m [ map(i,j) ]; k <= _M	[ map(i,j) ];	 k++) {
				b[k]=_G[map(i,j,k)] - _parameters->get_g()* _parameters->get_theta() * _parameters -> get_time_step()/_parameters->get_dxdydz(1) * ( _h [map(i,j+1)] - _h [map(i,j)] ) * _dz[map(i,j,k)];
			}

			solver->set_A_and_b(_A+map(i,j,0,0),b);
			solver->solve(TOL, MAXIT);

			for (int k = 0; k < _parameters->get_num_cells(2)+2 ; k++) {
				_v[map(i,j,k)]=x[k];
			}

		}
	}
	for (int k = 0; k <_parameters->get_num_cells(2)+2; k++) {
		for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
			_u [map(i,0,k)] = -_u [map(i,1,k)];
			_v [map(i,0,k)] = _v [map(i,1,k)];
			_u [map(i,_parameters->get_num_cells(1)+1,k)] = -_u [map(i,_parameters->get_num_cells(1),k)];
			_v [map(i,_parameters->get_num_cells(1)+1,k)] = _v [map(i,_parameters->get_num_cells(1),k)];
		}

		for (int j = 0; j <(_parameters->get_num_cells(1)+2); j++) {
			_u [map(0,j,k)] = _u [map(1,j,k)];
			_v [map(0,j,k)] = -_v [map(1,j,k)];
			_u [map(_parameters->get_num_cells(0)+1,j,k)] =_u [map(_parameters->get_num_cells(0),j,k)];
			_v [map(_parameters->get_num_cells(0)+1,j,k)] =-_v [map(_parameters->get_num_cells(0),j,k)];
		}
	}
}

void flowField::solve_q(){
	float TOL = 0.0001;
	int MAXIT = 1000000;
	float * x = new float [(_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2)*(_parameters->get_num_cells(2)+2)];

	for (int i = 0; i <(_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2)*(_parameters->get_num_cells(2)+2); i++) {
		x[i]=1;
	}

	this->update_P();
	this->update_R();

	Jacobi *solver = new Jacobi(_P, _R, x, (_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2)*(_parameters->get_num_cells(2)+2));
	solver->solve(TOL, MAXIT);
	
	delete solver;
	delete [] x;

}
void flowField::update_u_v_w(){}

void flowField::solve_h(){}

float* flowField::get_height() const{
	return _h;
}

float* flowField::get_DZ() const{
	return _dz;
}

void flowField::update_P(){
	float alpha =
	 _parameters->get_theta()
	 *_parameters->get_time_step()
	 / (_parameters->get_dxdydz(0) * _parameters->get_dxdydz(0));

	float beta =
	 _parameters->get_theta()
	 *_parameters->get_time_step()
	 / (_parameters->get_dxdydz(1) * _parameters->get_dxdydz(1));

	float gama = 
	 _parameters->get_theta()
	 *_parameters->get_time_step();

	//initialize the coeff matrix
	for (int i = 0; i <  (_parameters->get_num_cells(0)+2) *
					 (_parameters->get_num_cells(1)+2) *
					 (_parameters->get_num_cells(2)+2) *
					 (_parameters->get_num_cells(0)+2) *
				  	 (_parameters->get_num_cells(1)+2) *
				   	 (_parameters->get_num_cells(2)+2)
   					 ; i++	)
		_P  [i] = 0.0;

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			for (int k = 1; k < _parameters->get_num_cells(2)+1; k++) {
				_P	[map3d(map(i,j,k) , map(i,j,k))] =
									-alpha * _dz[map(i  ,j  ,k  )]
									-alpha * _dz[map(i-1,j  ,k  )]
									-beta  * _dz[map(i  ,j  ,k  )]
									-beta  * _dz[map(i  ,j-1,k  )]
									-gama  / _dz[map(i  ,j  ,k  )]
									-gama  / _dz[map(i  ,j  ,k-1)];
				_P	[map3d(map(i,j,k) , map(i+1,j,k))] = alpha * _dz[map(i  ,j  ,k  )];
				_P	[map3d(map(i,j,k) , map(i-1,j,k))] = alpha * _dz[map(i-1,j  ,k  )];
				_P	[map3d(map(i,j,k) , map(i,j+1,k))] = beta  * _dz[map(i  ,j  ,k  )];
				_P	[map3d(map(i,j,k) , map(i,j-1,k))] = beta  * _dz[map(i  ,j-1,k  )];
				_P	[map3d(map(i,j,k) , map(i,j,k+1))] = gama  / _dz[map(i  ,j  ,k  )];
				_P	[map3d(map(i,j,k) , map(i,j,k-1))] = gama  / _dz[map(i  ,j  ,k-1)];
			}
		}
	}
	
	//set the boundary coeffs
	for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
		for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
			_P	[map3d(map(0,j,k), map(0,j,k))] =  1;
			_P	[map3d(map(0,j,k), map(1,j,k))] = -1;
			
			_P	[map3d(map(_parameters->get_num_cells(0)+1 ,j,k), map(_parameters->get_num_cells(0)+1 ,j,k))] =  1;
			_P	[map3d(map(_parameters->get_num_cells(0)+1 ,j,k), map(_parameters->get_num_cells(0)   ,j,k))] = -1;
		}
	}

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
			_P	[map3d(map(i,0,k), map(i,0,k))] =  1;
			_P	[map3d(map(i,0,k), map(i,1,k))] = -1;
			
			_P	[map3d(map(i,_parameters->get_num_cells(1)+1,k), map(i,_parameters->get_num_cells(1)+1,k))] =  1;
			_P	[map3d(map(i,_parameters->get_num_cells(1)+1,k), map(i,_parameters->get_num_cells(1)  ,k))] = -1;
		}
	}
	
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			_P	[map3d(map(i,j,0), map(i,j,0))] =  1;
			_P	[map3d(map(i,j,0), map(i,j,1))] = -1;
			
			_P	[map3d(map(i,j,_parameters->get_num_cells(2)+1), map(i,j,_parameters->get_num_cells(2)+1))] =  1;
			_P	[map3d(map(i,j,_parameters->get_num_cells(2)+1), map(i,j,_parameters->get_num_cells(2)  ))] = -1;
		}
	}
}

void flowField::update_R(){

	for (int i = 0; i <  (	(_parameters->get_num_cells(0)+2) *
				(_parameters->get_num_cells(1)+2) *
				(_parameters->get_num_cells(2)+2)  )
   				; i++	)
		_R  [i] = 0.0;

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			for (int k = 1; k < _parameters->get_num_cells(2)+1; k++) {
				_R	[map(i,j,k)] =
							(_u[map(i,j,k)] * _dz[map(i,j,k)] - _u[map(i-1,j,k)] * _dz[map(i-1,j,k)])/(_parameters->get_dxdydz(0)) +
							(_v[map(i,j,k)] * _dz[map(i,j,k)] - _v[map(i,j-1,k)] * _dz[map(i,j-1,k)])/(_parameters->get_dxdydz(1)) +
							 _w[map(i,j,k)]                   - _w[map(i,j,k-1)];
			}
		}
	}

	//set the boundary coeffs
	for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
		for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
			_R	[map(0,j,k)] =  0;
			
			_R	[map(_parameters->get_num_cells(0)+1 ,j,k)] =  0;
		}
	}

	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
			_R	[map(i,0,k)] =  0;
			
			_R	[map(i,_parameters->get_num_cells(1)+1,k)] =  0;
		}
	}
	
	for (int i = 1; i < _parameters->get_num_cells(0)+1; i++) {
		for (int j = 1; j < _parameters->get_num_cells(1)+1; j++) {
			_R	[map(i,j,0)] =  0;
			
			_R	[map(i,j,_parameters->get_num_cells(2)+1)] =  0;
		}
	}
}

void flowField::print_data(){

	int i=1;
	int j=1;

	std::cout << "matrix A at position i=" << i << " and j=" << j << std::endl;
	for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
		for (int l = 0; l < _parameters->get_num_cells(2)+2; l++) {
			std::cout << std::setw(20)<<
			_A	[ map(i,j,k,l) ];
		}	
	std::cout << std::endl;
	}

	int k=3;
	std::cout << "matrix F" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_F	[ map(i,j,k) ];
		}
	std::cout << std::endl;
	}

	std::cout << "matrix G" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_G	[ map(i,j,k) ];
		}
	std::cout << std::endl;
	}

	std::cout << "matrix S" <<  std::endl;
	for (int i = 0; i < (_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2); i++) {
		for (int j = 0; j < (_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2); j++) {
			std::cout << std::setw(20)<<
			_S	[ map2d(i,j) ];
		}	
	std::cout << std::endl;
	}

	std::cout << "matrix T" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_T	[ map(i,j) ];
		}	
	std::cout << std::endl;
	}
	
	std::cout << "matrix h" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_h	[ map(i,j) ];
		}	
	std::cout << std::endl;
	}

	std::cout << "matrix u" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_u	[ map(i,j,k) ];
		}
	std::cout << std::endl;
	}

	std::cout << "matrix v" << std::endl;
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			std::cout << std::setw(20)<<
			_v	[ map(i,j,k) ];
		}
	std::cout << std::endl;
	}

	std::cout << "matrix P" << std::endl;
	for (int i = 0; i < (_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2)*(_parameters->get_num_cells(2)+2); i++) {
		for (int j = 0; j < (_parameters->get_num_cells(0)+2)*(_parameters->get_num_cells(1)+2)*(_parameters->get_num_cells(2)+2); j++) {
			std::cout << std::setw(5)<<
			_P	[ map3d(i,j) ];
		}	
	std::cout << std::endl;
	}

}

int flowField::map(int i, int j) const{ 
	return
			j +
			i * (_parameters->get_num_cells(1)+2) ;
}

int flowField::map2d(int i, int j) const{ 
	return
			j +
			i * (_parameters->get_num_cells(0)+2)
			  * (_parameters->get_num_cells(1)+2)	;
}

int flowField::map(int i, int j, int k) const{ 
	return 
			k +
			j * (_parameters->get_num_cells(2)+2) +
			i * (_parameters->get_num_cells(1)+2) *
		  		(_parameters->get_num_cells(2)+2) ;
}

int flowField::map3d(int i, int j) const{ 
	return 
			j +
			i * (_parameters->get_num_cells(0)+2)
			  * (_parameters->get_num_cells(1)+2)
			  * (_parameters->get_num_cells(2)+2)	;
}
int flowField::map(int i, int j, int k, int l) const{ 
	return 
			l +
			k * (_parameters->get_num_cells(2)+2) +
		   	j * (_parameters->get_num_cells(2)+2) *
				(_parameters->get_num_cells(2)+2) +
			i *	(_parameters->get_num_cells(2)+2) * 
				(_parameters->get_num_cells(2)+2) *
				(_parameters->get_num_cells(1)+2) ;
}

void flowField::test_solver(){
	float TOL = 0.0001;
	int MAXIT = 1000000;
	int N = 100;
//	float * A = new float [N*N];
//	float * b = new float [N];
//	float * x = new float [N];

	int i = 10;
	int j = 10;
	int k = _m [map(i,j)];
	float * A = _A;
	float * b = _dz;
	float * x = new float [_parameters->get_num_cells(2)+2];

	std::cout << "\033[1;34mFLOWFIELD: TEST SOLVER\033[0m" << std::endl;
/*
	for (int i = 0; i < N*N; i++) {
		A[i] = 0 ;
	}

	for (int i = 0; i < N; i++) {
		A[i+i*N] = -2;
	}

	for (int i = 0; i < N-1; i++) {
		A[i+i*N+1] = 1;
	}

	for (int i = 1; i < N; i++) {
		A[i+i*N-1] = 1;
	}

	for (int i = 0; i < N; i++) {
		b[i] = 1;
	}
*/
	for (int i = 0; i < _parameters->get_num_cells(2)+2 ; i++) {
		x[i]=1;
	}

	Solver *solver = new Jacobi(A, b, x, _parameters->get_num_cells(2)+2);
	solver -> solve(TOL, MAXIT);

	delete [] x; 
}
