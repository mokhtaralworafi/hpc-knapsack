#include "KnapSack.h"

KnapSack::KnapSack(double _capacity, int _maxNumPerItem, int _numOfItems)
{
	setCapacity(_capacity);
	setMaxNumPerItem(_maxNumPerItem);
	setNumOfItems(_numOfItems);
	setItems(new KnapSackItem[_numOfItems]);
}

KnapSack::KnapSack(const KnapSack& other)
	: capacity(other.capacity),
	  maxNumPerItem(other.maxNumPerItem),
	  numOfItems(other.numOfItems),
	  items(new KnapSackItem[other.numOfItems]){

	for(int i=0; i < numOfItems ;++i) {
		items[i].name = new std::string(other.items[i].name->c_str());
		items[i].weight = other.items[i].weight;
		items[i].worth = other.items[i].worth;
	}
}

KnapSack::~KnapSack()
{
	for(int i=0; i < numOfItems ;++i) {
		delete items[i].name;
		items[i].name = 0;
	}
	delete[] items;
}

KnapSack& KnapSack::operator =(KnapSack other) {

	swap(*this, other);
	return *this;

}

//***************************GETTERS********************************//
double KnapSack::getCapacity() const { return capacity; }
int KnapSack::getMaxNumPerItem() const { return maxNumPerItem; }
int KnapSack::getNumOfItems() const { return numOfItems; }
KnapSackItem* KnapSack::getItems() const { return items; }

//***************************SETTERS********************************//
void KnapSack::setCapacity(double _capacity){ capacity = _capacity; }
void KnapSack::setMaxNumPerItem(int _maxNumPerItem){ maxNumPerItem = _maxNumPerItem; }
void KnapSack::setNumOfItems(int _numOfItems){ numOfItems = _numOfItems; }
void KnapSack::setItems(KnapSackItem* _items){ items = _items; }


std::ostream& operator<<(std::ostream &strm, const KnapSack &v) {

	KnapSackItem* items = v.getItems();
	for (int i = 0; i < v.getNumOfItems(); i++)
	{
		strm << items[i].name->c_str() << " | " << items[i].weight << " | " << items[i].worth << "\n";
	}

	return strm;
}

void swap(KnapSack& first, KnapSack& second) {

	std::swap(first.capacity, second.capacity);
	std::swap(first.maxNumPerItem, second.maxNumPerItem);
	std::swap(first.numOfItems, second.numOfItems);
	std::swap(first.items, second.items);

}

