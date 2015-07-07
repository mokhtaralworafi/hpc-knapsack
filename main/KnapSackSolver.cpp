/*
 * KnapSackSolver.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: viktor
 */

#include "KnapSackSolver.h"

KnapSackSolver::KnapSackSolver(std::string inputFilename, std::string outputFilename, std::string algorithmName, int nrOfExecutions)
: knapSack(0,0),
  itemsOfSolution(),
  inputFilename(inputFilename),
  outputFilename(outputFilename),
  algorithmName(algorithmName),
  numberOfExecutions(nrOfExecutions),
  durationsOfExecutions()
{
	initKnapSack();
}

KnapSackSolver::~KnapSackSolver() {
	// TODO Auto-generated destructor stub
}

void KnapSackSolver::initKnapSack() {
	readInput();
}

void KnapSackSolver::readInput() {
	// TODO: maybe we should use a pointer otherwise we have to copy it here.
	knapSack = KnapSackReader::readKnapSackFrom(inputFilename.c_str());
}

void KnapSackSolver::start() {
	printf("Started %s\n", algorithmName.c_str());
	for (int i=0; i < numberOfExecutions ;++i) {
		executeOneRun();
	}
	writeStatistics();
}

void KnapSackSolver::executeOneRun() {
	printf("preparing ...\n");
	setUp();

	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	const int n = 10000,
	            r = 1000;
	const double flopsPerCalc = 2.0;

	printf("solving ...\n");

	start = getWalltime();

	solve();

	end = getWalltime();

	printf("finishing ...\n");
	tearDown();

	printWalltimeInSeconds(start, end);
	printGFLOPs( static_cast<double>(r) * static_cast<double>( n ), flopsPerCalc, elapsedSeconds( start, end ) );
	printf("\n");

	durationsOfExecutions.insert(durationsOfExecutions.end(), elapsedSeconds(start, end).count());
	writeSolution();
}

void KnapSackSolver::writeSolution() const {

	// Determine the amount of distinct knapSackItems
	std::vector<KnapSackItem> distinctItems;
	for(int i=0; i < itemsOfSolution.size() ;++i) {
		// Check if item is already in distinctItems
		bool itemIsNotAlreadyIncluded = true;
		for(int j=0; j < distinctItems.size() ;++j) {
			if (distinctItems[j] == itemsOfSolution[i]) {
				itemIsNotAlreadyIncluded = false;
				break;
			}
		}
		if (itemIsNotAlreadyIncluded) {
			distinctItems.insert(distinctItems.end(), itemsOfSolution[i]);
		}
	}

	// Create the file
	KnapSackWriter writer(outputFilename, distinctItems.size(), knapSack.getCapacity());

	for(int i=0; i < distinctItems.size() ;++i) {
		KnapSackItem& currItem = distinctItems[i];

		// Count number of exemplars
		int counter = 0;
		for (int j = 0; j < itemsOfSolution.size(); ++j) {
			if (currItem == itemsOfSolution[j])
				counter++;
		}
		assert(counter != 0);

		writer.addItem(&currItem, counter);
	}

	if ( ! writer.writeToFile()) {
		std::printf("Could not write to file.");
	}

}

void KnapSackSolver::writeStatistics() const {
	//calculate avg duration
	const int n = durationsOfExecutions.size();
	double sum = 0;
	for(int i=0; i<durationsOfExecutions.size(); i++){
		sum += durationsOfExecutions[i];
	}
	const double avg = sum / n;

	//calculate root mean square
	sum = 0;
	for(int i=0; i<durationsOfExecutions.size(); i++){
		sum += pow(durationsOfExecutions[i] - avg, 2);
	}
	const double rms = sqrt(sum / n);

	//TODO: remove demo print
	printf("***Statistics BEGIN***\n");
	printf("algorithm: %s\n", algorithmName.c_str());
	printf("number of executions: %d\n", numberOfExecutions);
	for(int i=0; i<durationsOfExecutions.size(); i++){
		printf("%d: %.4f\n", i, durationsOfExecutions[i]);
	}
	printf("avg: %.4f\n", avg);
	printf("rms: %.4f\n", rms);
	printf("***Statistics END***\n");

	//TODO: write statistics to file
}

void KnapSackSolver::setUp() {
	// Nothing to do in default implementation
}

void KnapSackSolver::tearDown() {
	// Nothing to do in default implementation
}
