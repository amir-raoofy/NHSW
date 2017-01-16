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
