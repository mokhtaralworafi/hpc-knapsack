class KnapSack{

	struct KnapSackItem{
		char* name;
		float weight;
		float worth;
	};

private:
	float capacity;
	int maxNumPerItem;
	int numOfItems;
	KnapSackItem** items;
	KnapSack();

	void setCapacity(float _capacity);
	void setMaxNumPerItem(int _maxNumPerItem);
	void setNumOfItems(int _numOfItems);
	void setItems(KnapSackItem** _items);

public:
	KnapSack(float _capacity, int _maxNumPerItem, int _numOfItems, KnapSackItem** _items);

	int getCapacity();
	int getMaxNumPerItem();
	int getNumOfItems();
	KnapSackItem** getItems();

};