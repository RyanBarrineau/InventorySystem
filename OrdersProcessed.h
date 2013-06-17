//PROG  :	Ryan Barrineau
//FILE	:	OrdersProcessed.h
//PURP	:	Opens, closes, and stores the parts and sales information throughout the day, in a file.
//			Allows access to the sales summary file, and can display the contents of the file
//			if needed. Also can give a total sales. 

class OrdersProcessed
{
private:
	int fileOpenSuccess;
	ofstream outInventorySummary;

public:
	OrdersProcessed(string);
	int getFileOpenSuccess();
	void saveRecord(string, int, int, double);
	void closeFile();
	void displayOrders(string);
	double totalCostOfOrders(string);

private:
	void openFile(string);
};

//constructor
OrdersProcessed::OrdersProcessed(string file)
{
	fileOpenSuccess = 0;
	outInventorySummary.open(file, ios::app);
	openFile(file);
}//END Constructor

//accessors
int OrdersProcessed::getFileOpenSuccess()
{
	return fileOpenSuccess;
}//END getFileOpenSuccess

//mutators
void OrdersProcessed::openFile(string fileName)
{
	if(!outInventorySummary.is_open())
		fileOpenSuccess = -1;
}//END openFile
void OrdersProcessed::saveRecord(string fileName, int partNumber, int quantity, double partTotal)
{
	outInventorySummary <<  partNumber << " " << quantity << " " << partTotal << endl;
}//END saveRecord
void OrdersProcessed::closeFile()
{
	outInventorySummary.close();
}//END closeFile
void OrdersProcessed::displayOrders(string fileName)
{
	int summaryCounter = 1;
	int partNumber;
	int quantity;
	double totalCost;

	ifstream outInventorySummary;
	outInventorySummary.open(fileName);
	if(outInventorySummary.is_open())
	{
		system("cls");
		cout << endl << "Trans #  Part #  Quantity  Total Cost" << endl
			 <<         "--------------------------------------" << endl;
		outInventorySummary >> partNumber >> quantity >> totalCost;
		while(!outInventorySummary.eof())
		{			
			cout << setw(3) << summaryCounter << setw(11) << partNumber << setw(7) << quantity << setw(8) << "$" << totalCost << endl;
			outInventorySummary >> partNumber >> quantity >> totalCost;
			summaryCounter++;
		}
	}
	else
		cout << endl << "File did not open!" << endl;
}//END displayOrders
double OrdersProcessed::totalCostOfOrders(string fileName)
{
	int partNumber;
	int quantity;
	double totalCost;
	double totalCostAccum = 0;

	ifstream outInventorySummary;
	outInventorySummary.open(fileName);
	if(outInventorySummary.is_open())
	{
		outInventorySummary >> partNumber >> quantity >> totalCost;
		while(!outInventorySummary.eof())
		{		
			totalCostAccum += totalCost;
			outInventorySummary >> partNumber >> quantity >> totalCost;			
		}
	}
	return totalCostAccum;
}//END totalCostOfOrders
