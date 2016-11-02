#include <string>
#include <fstream>
#include <sstream>
#include <flowField.h>

class Output {

    private:
		std::ofstream *_outputFile;
		std::stringstream _velocityStringStream;
		std::stringstream _pressureStringStream;
		const Parameters& _parameters;
		const flowField& _flowfield;
    public:

        Output(const Parameters& parameters, const flowField& flowfield);
		~Output ();

        void write (flowField & flowfield, int timeStep, std::string foldername);

        std::string getFilename(int timeStep, std::string foldername);
        void writeFileHeader();
        void writeGrid ();
        void writePressure();
        void writeVelocity();
        void writeHeight();
        void clearStringStreams();
};
