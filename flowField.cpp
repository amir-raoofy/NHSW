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
	_dz= new float [(_parameters->get_num_cells(0)+2)*
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
	}
}

void flowField::init_vel_field(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_u	[ map(i,j,k) ] = 1.0;
				_v	[ map(i,j,k) ] = 1.0;
				_w	[ map(i,j,k) ] = 1.0;
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
				_h	[ map(i,j) ] 	= _parameters->get_num_cells(2)
							  		* _parameters->get_dxdydz(2) 
								  	/ 2.0
							  		+ (i)
							 		*	(_parameters->get_num_cells(0))
							  		* _parameters->get_dxdydz(0) 
							  		/ 40.0 ;
		}
	}
}


void flowField::init_m(){
	for (int i = 0; i < (_parameters->get_num_cells(0)+2) *
				   		(_parameters->get_num_cells(1)+2)
						; i++){
		_m	[i] = 2;
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
				_A	[ map(i,j,k,k)]	=  alpha + _dz	[map (i,j,k) ];
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
			_A [ map(i,j,k,k) ] +=  _parameters->get_gamma_t() * _parameters->get_sim_time() * _parameters->get_u_a() ;
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
			_A [ map(i,j,k,k) ] +=  _parameters->get_gamma_t() * _parameters->get_sim_time() * _parameters->get_v_a() ;
		}
	}
}

void flowField::print_data(){
/*
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
				std::cout <<
					_h	[j +
					 	 i * (_parameters->get_num_cells(1)+2)  ]
						  << "\t"
						  <<
					_M	[j +
					 	 i * (_parameters->get_num_cells(1)+2)  ]
				<< std::endl;
		}
	}
*/	
/*	
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				for (int l = 0; l < _parameters->get_num_cells(2)+2; l++) {
				std::cout <<
				_A	[	l +
						k * (_parameters->get_num_cells(2)+2) +
					   	j * (_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(2)+2) +
						i *	(_parameters->get_num_cells(2)+2) * 
							(_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(1)+2) ]
				<< std::endl;
				}	
			}
		}
	}
*/
	int i=10;
	int j=10;

	std::cout << "matrix A at position i=" << i << " and j=" << j << std::endl;
	for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
		for (int l = 0; l < _parameters->get_num_cells(2)+2; l++) {
			std::cout << std::setw(20)<<
			_A	[ map(i,j,k,l) ];
		}	
	
	std::cout << std::endl;
	}
}

int flowField::map(int i, int j){ 
	return
			j +
			i * (_parameters->get_num_cells(1)+2) ;
}


int flowField::map(int i, int j, int k){ 
	return 
			k +
			j * (_parameters->get_num_cells(2)+2) +
			i * (_parameters->get_num_cells(1)+2) *
		  		(_parameters->get_num_cells(2)+2) ;
}

int flowField::map(int i, int j, int k, int l){ 
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
	float * A = new float [N*N];
	float * b = new float [N];
	float * x = new float [N];

	std::cout << "\033[1;34mFLOWFIELD: TEST SOLVER\033[0m" << std::endl;

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

	for (int i = 0; i < N; i++) {
		x[i]=1;
	}


	Solver *solver = new Jacobi(A, b, x, N);
	solver -> solve(TOL, MAXIT);

	delete [] A, b, x; 
}
