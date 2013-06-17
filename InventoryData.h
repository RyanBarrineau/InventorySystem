//PROG  :	Ryan Barrineau
//FILE	:	InventoryData.h
//PURP	:	To load data from a file into an array and then process the data.
//			Processing includes searching the array for a part number and then
//			returning it's part number and price.

class InventoryData
{
private:
	int partNum[200];
	double price[200];
	int recordCount;

public:
	InventoryData();
	int getRecordCount();
	int getPartNum(int);
	double getPrice(int);
	void loadArray(const string);
	void bubbleSort();
	void displayArray();
	int seqSearch(int);
	int binSearch(int);
};
//constructor
InventoryData::InventoryData()
{
	recordCount = 0;
	for(int ct = 0; ct < 200; ++ct) partNum[ct] = 0;
	for(int ct = 0; ct < 200; ++ct) price[ct] = 0;
}
//accessors
int InventoryData::getRecordCount()
{
	return recordCount;
}
int InventoryData::getPartNum(int target)
{
	return partNum[target]; 
}
double InventoryData::getPrice(int target)
{
	return price[target];
}
//mutators
void InventoryData::loadArray(const string file)
{
	ifstream inventoryIn;
	inventoryIn.open(file);
	if(inventoryIn.is_open())
	{
		inventoryIn >> partNum[recordCount] >> price[recordCount];
		while(!inventoryIn.eof())
		{
			++recordCount;
			inventoryIn >> partNum[recordCount] >> price[recordCount];
		}//END while

		inventoryIn.close();
	}//END if file opened
	else
	{
		recordCount = -1;
		cout << endl << "ERROR! Please check the file: " << file << endl << endl;
	}
}//END loadArray
void InventoryData::bubbleSort()
{
	int last, swap, index, partNumTemp = 0;
	double priceTemp;

	last = recordCount - 1;
	while(last > 0)
	{
		index = 0;
		swap = 0;

		while(index < last)
		{
			if(partNum[index] > partNum[index + 1])
			{
				partNumTemp = partNum[index];
				priceTemp = price[index];
				partNum[index] = partNum[index + 1];
				price[index] = price[index + 1];
				partNum[index + 1] = partNumTemp;
				price[index + 1] = priceTemp;
				swap = 1;
			}
			else
				++index;
		}
		if(swap == 0)
			last = 0;
		else
			last = last - 1;
	}
}//END bubbleSort
void InventoryData::displayArray()
{
	if(recordCount != -1)
	{
		cout << "The inventory file contains the following: " << endl;
		for(int count = 0; count < recordCount; count++)
		{
			cout << partNum[count] << "  " << price[count] << endl;
		}
	}
	else
		cout << "Cannot process without data." << endl;
}//END displayArray
int InventoryData::seqSearch(int partNumber)
{
	int count = 0;
	int found = -1;

	while(count < recordCount)
	{
		if(partNumber == partNum[count])
		{
			found = count;
			count = recordCount;
		}			
		else
			++count;

	}
	return found;
}//END seqSearch
int InventoryData::binSearch(int partNumber)
{
	int first = 0;
	int middle = 0;
	int last = recordCount - 1;
	int found = 0;

	while(first <= last && found == 0)
	{
		middle = (first + last) / 2;
		if(partNum[middle] == partNumber)
		{
			found = 1;
		}
		else if(partNum[middle] < partNumber)
			first = middle + 1;
		else
			last = middle -1;
	}
	if(found == 0)
		middle = -1;
	
	return middle;
}//END binSearch
