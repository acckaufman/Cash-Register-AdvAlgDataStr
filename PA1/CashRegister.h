//Amanda Kaufman
//Programming Assignment 1
//CISS 350A
//This class functions as a cash register, processing a customer's order for an employee.

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

//Structure to hold an individual product's information
struct Product
{
	int productNum;
	string description;
	double price;
	char taxable;
};

//Constants
const int MAX_PRODUCTS = 50;	//Maximum number of products the inventory array can hold
const int MIN_PROD_QTY = 1;		//Minimum number of one product the customer can order
const int MAX_PROD_QTY = 100;	//Maximum number of one product a customer can order
const double TAX_RATE = 0.075;	//Sales tax rate on taxable items

class CashRegister
{
private:
	int customerNum;
	Product inventory[MAX_PRODUCTS];
public:
	//###########################################################################################
	//Constructors																				#
	//###########################################################################################

	//Default Constructor
	CashRegister() {}
	//Destructor
	~CashRegister() {}

	//Initialize sets up the Product array and initializes customer number to 0.
	//The name of the input file is passed to the function as a string.
	bool initialize(string input)
	{
		//Set the number of customers to 0.
		customerNum = 0;

		//Set up the array with default values.
		Product initializeTemp;
		initializeTemp.productNum = 0;		//Initialize product numbers to 0
		initializeTemp.description = " ";	//Initialize descriptions to blank string
		initializeTemp.price = 0;			//Initialize prices to 0
		initializeTemp.taxable = 'N';		//Initialize taxable to 'N' by default

		for (int count = 0; count < MAX_PRODUCTS; count++)
		{
			inventory[count] = initializeTemp;
		}

		//Create local variables for array processing.
		int arrayIndex = 0;
		int firstNum = 0;
		int secondNum = 0;

		//Create local Product object for array processing.
		Product temp;

		//Open the inventory file.
		ifstream inputFile;
		inputFile.open(input);

		//Display an error message if the inventory file could not be opened.
		if (inputFile.fail())
		{
			cout << "Error: The inventory file does not exist.\n\n";
			return false;
		}

		//If the file was opened, process it as long as:
		//1. A number can be read from the file (not empty)
		//2. The number read was not zero
		//3. The arrayIndex has not surpassed the number of products allowed
		else
		{
			inputFile >> secondNum;

			//If secondNum is read as zero on the first pass, the file is empty.  Notify the user as a courtesy.
			if (secondNum == 0)
			{
				cout << "Note: No inventory information stored in the source file.\n\n";
				return false;
			}


			while (secondNum != 0 && arrayIndex < MAX_PRODUCTS)
			{
				try {
					if (firstNum == secondNum)	//If two product numbers are equal, throw an exception.
					{
						inputFile >> temp.description;	//Read the rest of the information
						inputFile >> temp.price;		//from the input file to clear it out
						inputFile >> temp.taxable;		//(Note: this Product object will not be stored)
						inputFile >> secondNum;
						throw string("Error: Two product numbers are the same. ");
					}
					else  //Otherwise, read lines from input file and store in local Product object.
					{
						temp.productNum = secondNum;
						inputFile >> temp.description;
						inputFile >> temp.price;
						inputFile >> temp.taxable;
						inventory[arrayIndex] = temp;	//Store the entry in the inventory array and
						arrayIndex++;					//Move to the next position in the inventory array.
						firstNum = secondNum;			//firstNum serves as a reference for if statement checking if two product numbers are the same.
						inputFile >> secondNum;
					}

				}

				//If a duplicate product number is found, tell the user which product numbers were duplicates.
				catch (string message)
				{
					cout << "Duplicate product #" << (arrayIndex + 1) << ".\n";
				}
			}

			//If the arrayIndex surpassed MAX_PRODUCTS before all items were read
			//(there were extra items left unread), inform the user as a courtesy.
			inputFile >> secondNum;
			if (secondNum != 0)  //The last number read before loop termination was not 0
			{
				cout << "Note: Inventory file too full - not all items were loaded.\n";
				cout << "Max number of items allowed is " << MAX_PRODUCTS << ".\n\n";
			}
			//Close the inventory file.
			inputFile.close();
			
			return true;
		}
	}

	//###########################################################################################
	//Accessor Functions																		#
	//###########################################################################################

	//getCustomerNumber returns the value currently in customerNum.
	int getCustomerNumber() const
	{
		return customerNum;
	}

	//getProduct returns the Product object stored in the inventory array at the index location
	//passed to the function.
	Product getProduct(int index) const
	{
		Product temp;
		temp.productNum = 0;
		temp.description = "no-data";
		temp.price = 0;
		temp.taxable = 'N';

		if (index < 0 || index > MAX_PRODUCTS)
		{
			cout << "Error: Index must be within valid range of 0 to " << MAX_PRODUCTS << ".\n";
			return temp;
		}
		else
			return inventory[index];
	}

	//printInvProduct prints a line of text to the specified output file, containing the product
	//information stored at the index location passed to the function.
	//Note: This function assumes that the output file exists and has already been opened.
	void printInventoryProd(ofstream &outputFile, int index)
	{
		//If index is within the valid range and the product number located at index is not 0,
		//print the product information to the output file.
		if (index >= 0 && index < MAX_PRODUCTS && inventory[index].productNum != 0)
		{
			outputFile << inventory[index].productNum << " "
				<< inventory[index].description << " "
				<< inventory[index].price << " "
				<< inventory[index].taxable << "\n";
		}
	}

	//printOrderedProd prints a line of text to the specified output file, containing essential
	//information on a product ordered by the customer.
	//The function prints description, quantity, unit cost, total price, and whether or not
	//the product is taxed.
	//Note: This function assumes that the output file exists and has already been opened.
	//It also assumes that the client handles input validation for qty (within valid range).
	void printOrderedProd(ofstream &outputFile, Product object, int qty)
	{
		outputFile << "\t" << left << setw(14) << object.description << " "
			<< setw(4) << right << qty << " @ " << setw(8) << fixed << showpoint << setprecision(2) << object.price << "\t"
			<< setw(8) << (qty * object.price) << " ";

		//If the product is taxable, append "TAX" to the end of the summary line.
		//Otherwise, simply move on to the next line.
		if (object.taxable == 'T' || object.taxable == 't')
			outputFile << "+ TAX" << endl;
		else
			outputFile << endl;
	}

	//###########################################################################################
	//Mutator Functions																			#
	//###########################################################################################

	//setCustomerNumber manually sets the number of customers that have been processed.
	void setCustomerNumber(int num)
	{
		if (num < 0)
			cout << "Error: customer number must be a positive integer.\n";
		else
			customerNum = num;
	}

	//setProduct manually adds a product into the inventory array at the index passed to the
	//function.
	//Note: This function assumes that the Product object  passed to it contains valid information.
	void setProduct(Product object, int index)
	{
		if (index >= 0 && index < MAX_PRODUCTS)
			inventory[index] = object;
		else
			cout << "Error! Index outside of valid range.\n";
	}

	//createOrder creates a new customer order and saves the output to a file as a receipt.
	//Must pass name of desired output file to this function as a parameter.
	void createOrder(ofstream &outputFile)
	{
		//Create local variables for processing the array.
		int prodNum = 0;
		int qty = 0;
		int foundIndex = 0;
		bool found = false;
		double subtotal;
		double taxtotal;
		char again = 'n';	//Ask the user if they want to create another order (y/n)

		//Print full inventory information stored in the inventory array.
		outputFile << "Inventory Information:\n\n";
		for (int index = 0; index < MAX_PRODUCTS; index++)
		{
				printInventoryProd(outputFile, index);
		}
		outputFile << "0\n";

		do
		{
			customerNum++;	//Increment the customer number to establish a new customer.
			subtotal = 0;	//Reset the subtotal accumulator
			taxtotal = 0;	//Reset the tax accumulator

			outputFile << "\n------------------------------------\n\n";

			//Need to find a way to print date and time to customer receipt

			outputFile << "Order Receipt" << endl;
			outputFile << "Customer #" << customerNum << endl << endl;

			//Get information for the product order from the employee and write to output file.
			cout << "Enter product number (0 to end order): ";
			cin >> prodNum;

			while (prodNum != 0)
			{
				while (prodNum < 0 || prodNum > 99999)
				{
					cout << "Error! Product number must be a positive integer of 5 digits\n"
						<< "or less.  Please try again.\n";
					cout << "Enter product number (0 to end order): ";
					cin >> prodNum;
				}

				//If the user has entered a nonzero number, search the array for it.
				if (prodNum != 0)	//Product number is entered
				{
					found = false;	//Reset the false flag
					try  //Try to find the product number in array
					{
						for (int index = 0; index < MAX_PRODUCTS; index++)  //Search the array for the product
						{
							if (inventory[index].productNum == prodNum) //Product is found
							{
								found = true;
								foundIndex = index;		//Store index at which product was found in the array.
							}
						} //end for loop

						  //Default case: product not found - throw exception and continue processing.
						if (found == false)
							throw int(prodNum);
						//If the product was found, try to get the quantity from the user.
						else
						{
							do {
								try
								{
									cout << "Enter quantity: ";
									cin >> qty;
									if (qty < MIN_PROD_QTY || qty > MAX_PROD_QTY)
										throw int(qty);
								}
								catch (int num)
								{
									cout << "Error: " << num << " is out of range. Please try again.\n";
									cout << "Enter quantity: ";
									cin >> qty;
									if (qty < MIN_PROD_QTY || qty > MAX_PROD_QTY)
										cout << "Error: " << qty << " is out of range.  Please try again.\n";
								}
							} while (qty < MIN_PROD_QTY || qty > MAX_PROD_QTY);
						}
						if (found == true)	//If the product was found and quantity is valid
						{
							printOrderedProd(outputFile, inventory[foundIndex], qty);		//write the order information to the output file.
							subtotal += (inventory[foundIndex].price * qty);				//Add the price * quantity of the found item to the subtotal
							if (inventory[foundIndex].taxable == 't' || inventory[foundIndex].taxable == 'T')	//If the inventory item is taxable, then
								taxtotal += (inventory[foundIndex].price * qty * TAX_RATE);						//add the tax on the cost of the products to the tax total
						}
					}
					catch (int num)
					{
						cout << "Error: Product #" << num << " not in inventory.\n";
						outputFile << "\t***Item " << num << " not in inventory.***\n";
					}

					//Whether the last product was found or not, continue by asking for the next product number.
					cout << "Enter next product number (0 to end order): ";
					cin >> prodNum;
				}
			}

			//Print subtotal and tax to output file
			outputFile << endl << "\t\t" << left << setw(10) << "Subtotal: " << fixed << showpoint << setprecision(2) << subtotal << endl;
			outputFile << "\t\t" << left << setw(10) << "Tax: " << fixed << showpoint << setprecision(2) << taxtotal << endl << endl;
			outputFile << "\tTotal: " << fixed << showpoint << setprecision(2) << static_cast<double>(subtotal + taxtotal) << endl;

			//Output instructions to the screen.
			cout << "End of order.\n";
			cout << "Receipt printed to output file.\n\n";
			cout << "Would you like to process another customer order? (y/n): ";
			cin >> again;
		} while (again == 'y' || again == 'Y');
	}
};

