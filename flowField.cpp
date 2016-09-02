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
						(_parameters->get_num_cells(2)+2)* 
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
				_u	[		k +
							j * (_parameters->get_num_cells(2)+2) +
							i * (_parameters->get_num_cells(1)+2) *
								(_parameters->get_num_cells(2)+2)	 ] = 1.0;
				_v	[		k +
							j * (_parameters->get_num_cells(2)+2) +
							i * (_parameters->get_num_cells(1)+2) *
								(_parameters->get_num_cells(2)+2)	 ] = 1.0;
				_w	[		k +
							j * (_parameters->get_num_cells(2)+2) +
							i * (_parameters->get_num_cells(1)+2) *
								(_parameters->get_num_cells(2)+2)	 ] = 1.0;
			}
		}
	}
}

void flowField::init_dz(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_dz	[		k +
							j * (_parameters->get_num_cells(2)+2) +
							i * (_parameters->get_num_cells(1)+2) *
								(_parameters->get_num_cells(2)+2)	 ] 
							= 	 _parameters->get_dxdydz(2);
			}
		}
	}
}

void flowField::init_h(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
				_h	[		j +
							i * (_parameters->get_num_cells(1)+2) ] 
							=   _parameters->get_num_cells(2)
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
				_A	[	k +
						k * (_parameters->get_num_cells(2)+2) +
					   	j * (_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(2)+2) +
						i *	(_parameters->get_num_cells(2)+2) * 
							(_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(1)+2) ]
						=  1.0;
			}
			for (int k =  _m	[	j +
								    i * (_parameters->get_num_cells(1)+2) ];
					 k <= _M	[	j +
								    i * (_parameters->get_num_cells(1)+2) ];
					 k++) {
				_A	[	k +
						k * (_parameters->get_num_cells(2)+2) +
					   	j * (_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(2)+2) +
						i *	(_parameters->get_num_cells(2)+2) * 
							(_parameters->get_num_cells(2)+2) *
							(_parameters->get_num_cells(1)+2) ]
						=  alpha
						+  _dz	[k +
								 j * (_parameters->get_num_cells(2)+2) +
								 i * (_parameters->get_num_cells(1)+2) *
								   	 (_parameters->get_num_cells(2)+2)	 ];
				if (k!=(_parameters->get_num_cells(2)+1)) 
					_A	[	k + 1 +
							k * (_parameters->get_num_cells(2)+2) +
						   	j * (_parameters->get_num_cells(2)+2) *
								(_parameters->get_num_cells(2)+2) +
							i *	(_parameters->get_num_cells(2)+2) * 
								(_parameters->get_num_cells(2)+2) *
								(_parameters->get_num_cells(1)+2) ]
							=  -alpha;
				if (k!=0)
					_A	[	k - 1 +
							k * (_parameters->get_num_cells(2)+2) +
						   	j * (_parameters->get_num_cells(2)+2) *
								(_parameters->get_num_cells(2)+2) +
							i *	(_parameters->get_num_cells(2)+2) * 
								(_parameters->get_num_cells(2)+2) *
								(_parameters->get_num_cells(1)+2) ]
							=  -alpha;
			}

			int k =  _m	[j +
						 i * (_parameters->get_num_cells(1)+2) ];
			_A	[	k +
					k * (_parameters->get_num_cells(2)+2) +
				   	j * (_parameters->get_num_cells(2)+2) *
						(_parameters->get_num_cells(2)+2) +
					i *	(_parameters->get_num_cells(2)+2) * 
						(_parameters->get_num_cells(2)+2) *
						(_parameters->get_num_cells(1)+2) ]
					+=  _parameters->get_gamma_b() * _parameters->get_sim_time();

			k =  _M	[j +
					 i * (_parameters->get_num_cells(1)+2) ];
			_A	[	k +
					k * (_parameters->get_num_cells(2)+2) +
				   	j * (_parameters->get_num_cells(2)+2) *
						(_parameters->get_num_cells(2)+2) +
					i *	(_parameters->get_num_cells(2)+2) * 
						(_parameters->get_num_cells(2)+2) *
						(_parameters->get_num_cells(1)+2) ]
					+=  _parameters->get_gamma_t() * _parameters->get_sim_time();

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
		_A	[	l +
				k * (_parameters->get_num_cells(2)+2) +
			   	j * (_parameters->get_num_cells(2)+2) *
					(_parameters->get_num_cells(2)+2) +
				i *	(_parameters->get_num_cells(2)+2) * 
					(_parameters->get_num_cells(2)+2) *
					(_parameters->get_num_cells(1)+2) ];
		}	
	
	std::cout << std::endl;
	}
}
