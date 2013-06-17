//PROG  :	Ryan Barrineau
//FILE	:	Inventory Price Search.cpp
//PURP	:	To search for an item in inventory and return it's price.
//			The user enters a part number, it is searched for in an array, and if found,
//			it's part number and price is returned. The user will then
//			be able to choose a quantity. If the part number is not found the 
//			program will tell the user. When the user exits, a summary for the day will be displayed.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <sstream>
using namespace std;

#include "InventoryData.h"
#include "OrdersProcessed.h"

//function prototypes
void displayBanner();
int nonIntCheckPart(char *message);
int nonIntCheckQuant(char *message);

int main()
{
	int partCode = 0;
	int binTarget = 0;
	int summaryCounter = 0;
	char date[9];
	int quantity = 0;
	double partTotal = 0;

	const string OPEN_FILE = "masterInventory.dat";
	const string SAVE_FILE = "ordersProcessed.dat";

	_strdate_s(date);

	InventoryData partInventory;
	OrdersProcessed todaySummary(SAVE_FILE);
	partInventory.loadArray(OPEN_FILE);
	if(partInventory.getRecordCount() != -1)
	{
		partInventory.bubbleSort();
		while(partCode != -1)
		{
			displayBanner();
			partCode = nonIntCheckPart("Enter 5-digit part code to lookup price(enter -1 to exit): ");
				
			if(partCode != -1)
			{						
				binTarget = partInventory.binSearch(partCode);
				if(binTarget != -1)
				{
					cout << "-----------------------------------------------------------------" << endl;
					cout << "Found part number " << partInventory.getPartNum(binTarget) << ", and its price is $" 
						 << fixed << setprecision(2) << partInventory.getPrice(binTarget) << endl << endl;
					quantity = nonIntCheckQuant("Quantity: ");
					partTotal = quantity * partInventory.getPrice(binTarget);
					cout << endl << "PartID#    Price  Qty Ordered  Total" << endl
						 << "--------------------------------------------" << endl;
					cout << " " << partInventory.getPartNum(binTarget) << "     " << partInventory.getPrice(binTarget) << "      " 
						 << quantity << "       $" << setprecision(2) << partTotal << endl << endl;
						
					if (todaySummary.getFileOpenSuccess() != -1)
						todaySummary.saveRecord(SAVE_FILE, partInventory.getPartNum(binTarget), quantity, partTotal);
					else
						cout << endl << SAVE_FILE << " did not open" << endl;
				}
				else
				{
					cout << "Part number was not found!" << endl << endl;
				}				
			system("pause");
		    system("cls");
			}
		}//END while

		todaySummary.displayOrders(SAVE_FILE);
		cout << endl << "Total sales on " << date << ": $" << todaySummary.totalCostOfOrders(SAVE_FILE) << endl << endl;
		todaySummary.closeFile();
		system("pause");
	}
	else
	{
		system("pause");	
	}
	return 0;
}
//***************Function Definitions****************************************************
void displayBanner()
{
	cout << " ######                                    #                        " << endl
         << " #     #   ##   #####  #    #  ####       # #   #    # #####  ####  " << endl
         << " #     #  #  #  #    # #   #  #          #   #  #    #   #   #    # " << endl
         << " ######  #    # #    # ####    ####     #     # #    #   #   #    # " << endl		
		 << " #       ###### #####  #  #        #    ####### #    #   #   #    # " << endl
		 << " #       #    # #   #  #   #  #    #    #     # #    #   #   #    # " << endl
		 << " #       #    # #    # #    #  ####     #     #  ####    #    ####  " << endl << endl;
                                                                    
	cout << " ######                                 ######    ###     #####          " << endl
		 << " #     #   ##   #####  #####  ####      #     #    #     #     #         " << endl
		 << " #     #  #  #  #    #   #   #          #     #    #     #               " << endl
		 << " ######  #    # #    #   #    ####      ######     #      #####          " << endl
		 << " #       ###### #####    #        #     #          #           #         " << endl
		 << " #       #    # #   #    #   #    #     #          #     #     #         " << endl
		 << " #       #    # #    #   #    ####      # #       ### #   ##### #       " << endl;
	cout << "---------------------------------------------------------------------" << endl << endl;
	cout << "This Parts Inventory System will search for a part and return it's price if found" << endl << endl;
}//END displayBanner
int nonIntCheckPart(char *message)
{
	int out;
	string in;

	while(true)
	{
		cout << message;
		getline(cin,in);
		stringstream ss(in);

		if(ss >> out && !(ss >> in)) 
			return out;

		cin.clear();
		cerr << endl << "-------------------------------------------------------------" << endl 
			 << "Invalid input! Part codes are only whole numbers. (example: 11111)" << endl << endl
			 << "Please try again." << endl << endl << endl << endl;
	}
}//END nonIntCheckPart
int nonIntCheckQuant(char *message)
{
	int out;
	string in;

	while(true)
	{
		cout << message;
		getline(cin,in);
		stringstream ss(in);

		if(ss >> out && !(ss >> in) && (out > 0)) 
			return out;

		cin.clear();
		cerr << endl << "-------------------------------------------------------------" << endl 
			 << "Invalid input! Quantity is only a whole number. (example: 22)" << endl << endl
			 << "Please try again." << endl << endl << endl;
	}
}//END nonIntCheckQuant
