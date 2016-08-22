#include <flowField.h>

int main(int argc, const char *argv[])
{
	Parameters *parameters = new Parameters();
	parameters -> parse(argc, argv);
	parameters -> print_parameters();
	return 0;
}
