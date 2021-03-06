#include "output.h"

Output::Output(const Parameters& parameters, FlowField& flowfield): outputFile_ (*new std::ofstream), parameters_(parameters), flowField_(flowfield){
	velocityStringStream_ << std::fixed << std::setprecision(6);
	pressureStringStream_ << std::fixed << std::setprecision(6);
}

Output::~Output () {
	delete &outputFile_;
}

void Output::write (int timeStep, std::string foldername ) {

	if (parameters_.topology.id==0) {
		if (timeStep%parameters_.GetOutFreq()==0) 	
			std::cout << "=== Writing VTK Output ===" << std::endl;
	}
	// Open the file and set precision
	outputFile_.open(this->getFilename(timeStep, foldername).c_str());
	outputFile_ << std::fixed << std::setprecision(6);
	// Output the different sections of the file
	this->writeFileHeader();
	this->writeGrid();
	this->writePressure();
	this->writeHeight();
	//this->writebathymetry();
	this->writeVelocity();
	this->writeDZ();
  //this->writeQ();
	
	// Close the file
	outputFile_.close();
	
	this->clearStringStreams();
	
}

void Output::writeFileHeader(){
	outputFile_ << "# vtk DataFile Version 2.0" << std::endl;
	outputFile_ << "Output file for NHSW written by Amir Raoofy" << std::endl;
	outputFile_ << "ASCII" << std::endl << std::endl;
}

void Output::writeGrid (){
	outputFile_ << "DATASET STRUCTURED_GRID" << std::endl;
	outputFile_ << "DIMENSIONS " <<  parameters_.get_num_cells(0)+1 << " "
						   			    <<  parameters_.get_num_cells(1)+1 << " " 
										<<  parameters_.get_num_cells(2)+1 << std::endl;
	outputFile_ << "POINTS " 	<< (parameters_.get_num_cells(0)+1)
		  								  *(parameters_.get_num_cells(1)+1)
										  *(parameters_.get_num_cells(2)+1) << " float" << std::endl;
	
	for (int k = 0; k < parameters_.get_num_cells(2)+1; k++) {
		for (int j = 0; j < parameters_.get_num_cells(1)+1; j++) {
			for (int i = 0; i < parameters_.get_num_cells(0)+1; i++) {
				outputFile_ 	<< parameters_.topology.id_x * parameters_.GetCubeLength(0)/ parameters_.topology.npx + parameters_.get_dxdydz(0) *i << " "
   								<< parameters_.topology.id_y * parameters_.GetCubeLength(1)/ parameters_.topology.npy + parameters_.get_dxdydz(1) *j << " " 
   								<<  parameters_.get_dxdydz(2) *k << std::endl;
			}
		}	
	}
}

void Output::writePressure (){}

void Output::writeVelocity (){
	outputFile_ <<"VECTORS velocity float" << std::endl;
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		for (int j = 0; j < parameters_.get_num_cells(1); j++) {
			for (int i = 0; i < parameters_.get_num_cells(0); i++) {
				outputFile_ << ( flowField_.u[map(i,j,k)] + flowField_.u[map(i+1,j,k)] ) /2 << " " <<
											 ( flowField_.v[map(i,j,k)] + flowField_.v[map(i,j+1,k)] ) /2 << " " <<
											 ( flowField_.w[map(i,j,k)] + flowField_.w[map(i,j,k+1)] ) /2 << std::endl;
			}
		}
	}
}

void Output::writeHeight (){
	outputFile_ << "CELL_DATA " 	<< parameters_.get_num_cells(0) 
                                      *  parameters_.get_num_cells(1)
                                      *  parameters_.get_num_cells(2) << std::endl;
	outputFile_ << "SCALARS height float 1" << std::endl;
	outputFile_ << "LOOKUP_TABLE default" << std::endl;		
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
				outputFile_ << flowField_.etta[map(i,j)] << std::endl;
			}
		}	
	}

	outputFile_ << std::endl;
}

void Output::writeBathymetry (){
	outputFile_ << "CELL_DATA " 	<< parameters_.get_num_cells(0) 
		   								*  parameters_.get_num_cells(1)	<< std::endl;
	outputFile_ << "SCALARS bathymetry float 1" << std::endl;
	outputFile_ << "LOOKUP_TABLE default" << std::endl;		
	for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
		for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
			outputFile_ << flowField_.m[map(i,j)] << std::endl;	
		}
	}	

	outputFile_ << std::endl;
}

std::string Output::getFilename( int timeStep, std::string foldername ) {	
	std::stringstream filename;
	filename << foldername << "/" << "output." << parameters_.topology.id << "." << timeStep << ".vtk";
	return filename.str();
}

void Output::clearStringStreams() {
	pressureStringStream_.str("");
	velocityStringStream_.str("");
}

void Output::writeDZ(){
	outputFile_ << "SCALARS dz float 1" << std::endl;
	outputFile_ << "LOOKUP_TABLE default" << std::endl;
	for (int k = 0; k < parameters_.get_num_cells(2); k++) {
		for (int j = 1; j < parameters_.get_num_cells(1)+1; j++) {
			for (int i = 1; i < parameters_.get_num_cells(0)+1; i++) {
				outputFile_ << flowField_.dz_i[map(i,j,k)] << std::endl;
			}
		}
	}

	outputFile_ << std::endl;
}
