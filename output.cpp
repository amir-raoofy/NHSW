#include <output.h>

Output::Output(const Parameters& parameters, const flowField& flowfield):_parameters(parameters), _flowfield(flowfield){
	this->_outputFile = new std::ofstream;
	this->_velocityStringStream << std::fixed << std::setprecision(6);
	this->_pressureStringStream << std::fixed << std::setprecision(6);
}

Output::~Output () {
	delete this->_outputFile;
}

void Output::write ( flowField & flowfield, int timeStep, std::string foldername ) {

	std::cout << "=== Writing VTK Output ===" << std::endl;
	
	// Open the file and set precision
	this->_outputFile->open(this->getFilename(timeStep, foldername).c_str());
	*this->_outputFile << std::fixed << std::setprecision(6);
	
	// Output the different sections of the file
	this->writeFileHeader();
	this->writeGrid();
	this->writePressure();
	this->writeVelocity();
	this->writeHeight();
	
	// Close the file
	this->_outputFile->close();
	
	this->clearStringStreams();
	
}

void Output::writeFileHeader(){
	*this->_outputFile << "# vtk DataFile Version 2.0" << std::endl;
	*this->_outputFile << "Output file for NHSW written by Amir Raoofy" << std::endl;
	*this->_outputFile << "ASCII" << std::endl << std::endl;
}

void Output::writeGrid (){
	*this->_outputFile << "DATASET STRUCTURED_GRID" << std::endl;
	*this->_outputFile << "DIMENSIONS " <<  _parameters.get_num_cells(0)+1 << " "
						   			    <<  _parameters.get_num_cells(1)+1 << " " 
										<<  _parameters.get_num_cells(2)+1 << std::endl;
	*this->_outputFile << "POINTS " 	<< (_parameters.get_num_cells(0)+1)
		  								  *(_parameters.get_num_cells(1)+1)
										  *(_parameters.get_num_cells(2)+1) << " float" << std::endl;
	
	for (int k = 0; k < _parameters.get_num_cells(2)+1; k++) {
		for (int j = 0; j < _parameters.get_num_cells(1)+1; j++) {
			for (int i = 0; i < _parameters.get_num_cells(0)+1; i++) {
				*this->_outputFile <<  _parameters.get_dxdydz(0) *i << " "
   								   <<  _parameters.get_dxdydz(1) *j << " " 
   								   <<  _parameters.get_dxdydz(2) *k << std::endl;
			}
		}	
	}
}

void Output::writePressure (){}
void Output::writeVelocity (){}
void Output::writeHeight (){
	*this->_outputFile << "CELL_DATA " 	<< _parameters.get_num_cells(0) 
		   								*  _parameters.get_num_cells(1)
										*  _parameters.get_num_cells(2) << std::endl;
	*this->_outputFile << "SCALARS height float 1" << std::endl;
	*this->_outputFile << "LOOKUP_TABLE default" << std::endl;		
	for (int k = 1; k < _parameters.get_num_cells(2)+1; k++) {
		for (int j = 1; j < _parameters.get_num_cells(1)+1; j++) {
			for (int i = 1; i < _parameters.get_num_cells(0)+1; i++) {
				*this->_outputFile << (this->_flowfield).get_height()[(this->_flowfield).map(i,j) ] << std::endl;
			}
		}	
	}

	*this->_outputFile << std::endl;
}

std::string Output::getFilename( int timeStep, std::string foldername ) {	
	std::stringstream filename;
	filename << foldername << "/" << "output." << timeStep << ".vtk";
	return filename.str();
}

void Output::clearStringStreams() {
	_pressureStringStream.str("");
	_velocityStringStream.str("");
}
