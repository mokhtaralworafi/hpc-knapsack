#include "KnapSackReader.h"

/*
*	Example File:
*
*	---------------------
*	10.0 4 2
*	XXL blue Ox		3.0 2.00
*	gray mouse		1.0 2.45
*	---------------------
*
*	Capacity = 10.0
*	MaxNumPerItem = 4
*	NumOfItems = 2
*	Item 1: Name(XXL blue Ox), Weight(3.0), Worth(2.00)
*	Item 2: Name(gray mouse), Weight(1.0), Worth(2.45)
*	Itemnames are always 13 characters long
*/

KnapSack KnapSackReader::readKnapSackFrom(const char* fileName){

	std::cout << "**************************" << std::endl;
	std::cout << "reading " << fileName << " ... " << std::endl;

	//allocate objects on stack by auto calling constructors ifstream(filename) and string()
	std::ifstream input(fileName);
	std::string strLine;

	//read first line: capacity, MaxNumPerItem and numOfItems
	std::getline(input, strLine);
	std::cout << "constraints: " << strLine << '\n';
	std::vector<std::string> firstLine = StringUtils::split(strLine, ' ');
	const double capacity = std::atof(firstLine[0].c_str());
	const int numOfInstancesPerItem = std::atoi(firstLine[1].c_str());
	const int numOfItems = std::atoi(firstLine[2].c_str());

	const int totalNumOfItems = numOfInstancesPerItem * numOfItems;
	KnapSack knapSack(capacity, totalNumOfItems);
	KnapSackItem* items = knapSack.getItems();

	//read / populate items
	int i = 0;
	while (std::getline(input, strLine)) {
		std::cout << "item: " << strLine << '\n';

		// Read name, weight and worth
		std::string* name = new std::string(strLine.substr(0, STRLENGTH_ITEMNAME));
		StringUtils::trim(*name);
		std::string valueString = strLine.substr(STRLENGTH_ITEMNAME + 1);
		std::vector<std::string> values = StringUtils::split(valueString, ' ');
		const double weight = std::atof(values[0].c_str());
		const double worth = std::atof(values[1].c_str());

		// Add item x times, where x is the number of possible instances per item
		for (int j = 0; j < numOfInstancesPerItem; j++){
			items[i].name = name;
			items[i].weight = weight;
			items[i].worth = worth;
			i++;
		}
	}

	std::cout << "reading complete" << std::endl;
	std::cout << "**************************" << std::endl;

	return knapSack;
}

