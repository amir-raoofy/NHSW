#include <string>
#include <fstream>
#include <sstream>
#include "FlowField.h"

class Output {

private:
	std::ofstream &outputFile_;
	std::stringstream velocityStringStream_;
	std::stringstream pressureStringStream_;
	const Parameters& parameters_;
	const FlowField& flowField_;

	inline int map(int i, int j){return j+i*(parameters_.get_num_cells(1)+2);}
	inline int map(int i, int j, int k){return k+j*parameters_.get_num_cells(2)
										        +i*(parameters_.get_num_cells(1)+2)*parameters_.get_num_cells(2);}
		
public:
    Output(const Parameters& parameters, FlowField& flowField);
	~Output ();

	void write (int timeStep, std::string folderName);

	std::string getFilename(int timeStep, std::string folderName);
    void writeFileHeader();
    void writeGrid ();
    void writePressure();
    void writeVelocity();
    void writeHeight();
	void writeBathymetry();
    void writeQ();
    void clearStringStreams();
    //@ Debug
	void writeDZ();
};
