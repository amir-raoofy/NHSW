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
					(_parameters->get_num_cells(2)+2)];
	_dz= new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_q = new float [(_parameters->get_num_cells(0)+2)*
					(_parameters->get_num_cells(1)+2)*
					(_parameters->get_num_cells(2)+2)];
	_h = new float [(_parameters->get_num_cells(0)+2)*
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
}

void flowField::init_vel_field(){
	for (int i = 0; i < _parameters->get_num_cells(0)+2; i++) {
		for (int j = 0; j < _parameters->get_num_cells(1)+2; j++) {
			for (int k = 0; k < _parameters->get_num_cells(2)+2; k++) {
				_u	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_v	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_w	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_F	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_G	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_A	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_dz	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
								(_parameters->get_num_cells(1)+2)	 ] = 0.0;
				_q	[		i +
							j + (_parameters->get_num_cells(0)+2) +
							k * (_parameters->get_num_cells(0)+2) *
							(_parameters->get_num_cells(1)+2)	 ] = 0.0;
			}
			_h	[		i +
						j + (_parameters->get_num_cells(0)+2)	 ] = 0.0;
		}
	}
}
