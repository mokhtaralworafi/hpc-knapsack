/**
 * Tests whether the parallel dynamic programming algorithm for solving the knapsack problem works correctly.
 */

#include "main/algorithms/DynamicProgrammingParallelSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

int testDPPSolver(const char* inputFile, const char* outputFile, const std::string* assumedContent, int assumedContentLength) {
	DynamicProgrammingParallelSolver* solver = new DynamicProgrammingParallelSolver(inputFile, outputFile);

	solver->start();

	delete solver;

	return TestUtils::checkOutput(assumedContent, assumedContentLength, outputFile);
}

int main(int argc, char* argv[]){
	int returnCode = testDPPSolver(KNAPSACK_INPUT_FILE_FIRST_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_1_DIFFERENT_ORDER_OF_ITEMS, ASSUMED_CONTENT_LINES_FILE_1);
	if (0 != returnCode)
		return 1;

	returnCode = testDPPSolver(KNAPSACK_INPUT_FILE_THIRD_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_3, ASSUMED_CONTENT_LINES_FILE_3);
	if (0 != returnCode)
		return 2;

	returnCode = testDPPSolver(KNAPSACK_INPUT_FILE_DP_EXAMPLE, TEST_OUTPUT_FILE,
			ASSUMED_CONTENT_FILE_DP, ASSUMED_CONTENT_LINES_FILE_DP);

	if (0 != returnCode)
		return 3;

	return returnCode;
}
