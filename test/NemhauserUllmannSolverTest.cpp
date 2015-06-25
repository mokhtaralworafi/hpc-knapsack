/**
 * Tests whether the brute force algorithm for solving the knapsack problem works correctly.
 */

#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "util/TestUtils.h"
#include "test/TestData.h"

/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00
 */

/* Expected Solution
 * -----------------------------------
 * 3x gray mouse -> 3 weight, 6 worth
 * 3x yellow daisy -> 12 weight, 30 worth
 * -----------------------------------
 * overall 15 weight and 36 worth
*/



/**/
const std::string ASSUMED_CONTENT[] {"Kapazität;15.0", "gray mouse;3", "yellow daisy;3", "Gesamtgewicht;15.0", "Gesamtwert;36.00"};
const int ASSUMED_CONTENT_LENGTH = 5;


int testNemhauserUllmannSolver(const char* inputFile, const char* outputFile, const std::string* assumedContent, int assumedContentLength) {
	NemhauserUllmannSolver* solver = new NemhauserUllmannSolver(inputFile, outputFile);

	solver->start();

	return TestUtils::checkOutput(assumedContent, assumedContentLength, outputFile);
}

int main(int argc, char* argv[]){
	int returnCode = testNemhauserUllmannSolver(KNAPSACK_INPUT_FILE_FIRST_EXAMPLE, TEST_OUTPUT_FILE,
												ASSUMED_CONTENT_FILE_1, ASSUMED_CONTENT_LINES_FILE_1);
	if (0 != returnCode)
		return 1;

	returnCode = testNemhauserUllmannSolver(KNAPSACK_INPUT_FILE_SECOND_EXAMPLE, TEST_OUTPUT_FILE,
												ASSUMED_CONTENT_FILE_2, ASSUMED_CONTENT_LINES_FILE_2);
	if (0 != returnCode)
		return 2;

	return returnCode;
}
