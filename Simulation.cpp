#include "Simulation.h"
#include "defaultScenario.h"

Simulation::Simulation(const Parameters& parameters, FlowField& flowField, CommunicationManager& communicationManager):
	parameters_(parameters),
	flowField_(flowField),
	communicationManager_(communicationManager)
	{
		time_step=parameters_.get_time_step();
		scenario_ = new defaultScenario(parameters,flowField, communicationManager);
	}

Simulation::~Simulation(){
	delete scenario_;
}

void Simulation::printTimeMeasurements(){

		this->setMeasuredData();
		int N= 4*(parameters_.get_num_cells(0)+2)*(parameters_.get_num_cells(1)+2)+
			   2*(parameters_.get_num_cells(0)  )*(parameters_.get_num_cells(1)  );
	std::cout 	<< " ==============================================================="<< std::endl;
	std::cout 	<< "|" << "\033[1;31m                        Measurment resutls                     \033[0m"
				<< "|" 	 <<  std::endl;
	std::cout 	<< " ==============================================================="<< std::endl;


		std::cout << std::left << std::setw(52) << "|Final iteration(TimeStep counts): " 				<< std::setw(11)	<< --it0_ 					<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Time spent in all iterations: " 					<< std::setw(11)	<< T0_ 						<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time spent in one TimeStep: " 				<< std::setw(11)	<< T0_/it0_ 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Time spent in 1D solvers in all TimeSteps: " 		<< std::setw(11)	<< T1_ 						<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time spent in 1D solvers in one TimeStep: "<< std::setw(11)	<< T1_/it0_ 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|portion of 1D solvers in all iterations (%): " 	<< std::setw(11)	<< 100*T1_/T0_ 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Total iteration count in all 1d solvers: "			<< std::setw(11)	<< it1_ 					<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average iteration count for 1d solves: "			<< std::setw(11)	<< it1_/(FLOAT)(it0_*N) 	<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Accumulative iteration count for 1d solves: "		<< std::setw(11)	<< it1_/(FLOAT)N	 		<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Iterations for all 1d solves in one time step: "	<< std::setw(11)	<< it1_/(FLOAT)it0_	 		<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time for one iteration in 1d solves: "		<< std::setw(11)	<< T1_/ it1_				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time for one 1d solve: "					<< std::setw(11)	<< T1_/ (FLOAT)(it0_*N) 	<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Accumulative average time for one 1d solve: "		<< std::setw(11)	<< T1_/ (N) 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Time spent in 2D solver in all TimeSteps: " 		<< std::setw(11)	<< T2_ 						<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time spent in 2D solver in one TimeStep: "	<< std::setw(11)	<< T2_/it0_ 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|portion of 2D solvers in all iterations (%): " 	<< std::setw(11)	<< 100*T2_/T0_ 				<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Total iteration count for all 2d solves: "			<< std::setw(11)	<< it2_ 					<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average iteration count for 2d solves: "			<< std::setw(11)	<< it2_/(FLOAT)it0_			<< " |" << std::endl;
		std::cout << std::left << std::setw(52) << "|Average time for one iteration in 2d solves: "		<< std::setw(11)	<< T2_/it2_ 				<< " |" << std::endl;
		std::cout << "\033[1;31m =============================================================== \033[0m"   													<< std::endl;

}

