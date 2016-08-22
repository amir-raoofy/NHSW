#include <flowField.h>

int main(int argc, const char *argv[])
{
	//Parameters* parameters = new Parameters();
	Parameters* parameters = new Parameters(argc, argv);
	parameters -> print_parameters();

	flowField* flowfield = new flowField(parameters);

	return 0;
}
