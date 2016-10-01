#include <flowField.h>

int main(int argc, const char *argv[])
{
	//Parameters* parameters = new Parameters();
	Parameters* parameters = new Parameters(argc, argv);
	parameters -> print_parameters();

	flowField* flowfield = new flowField(parameters);
	flowfield -> init_data();
	flowfield -> init_vel_field();
	flowfield -> init_dz();
	flowfield -> init_h();
	flowfield -> update_M();
	flowfield -> init_m();
	flowfield -> update_A();
	flowfield -> update_F();
	flowfield -> update_G();
	flowfield -> print_data();
	flowfield -> test_solver();
	return 0;
}
