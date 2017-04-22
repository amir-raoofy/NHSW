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
	void write2d (int timeStep, std::string folderName);
	void write2d_height (int timeStep, std::string folderName);
	void write2d_bathymetry (int timeStep, std::string folderName);

	std::string getFilename(int timeStep, std::string folderName);
	std::string getFilename_volume(int timeStep, std::string folderName);
	std::string getFilename_bathymetry(int timeStep, std::string folderName);
	std::string getFilename_height(int timeStep, std::string folderName);
    void writeFileHeader();
    void writeGrid2d();
    void writeGrid2d_height();
    void writeGrid2d_bathymetry();
    void writeGrid3d();
    void writePressure();
    void writeVelocity();
    void writeHeight();
    void writeHeight2d();
    void writeHeight2d_2();
	void writeBathymetry();
	void writeBathymetry_2();
    void writeQ();
    void clearStringStreams();
    //@ Debug
	void writeDZ();
};
