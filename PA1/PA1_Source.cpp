//Amanda Kaufman
//Programming Assignment 1
//CISS 350A
//This program functions as a cash register, processing a customer's order for an employee.

#include "CashRegister.h"

int main()
{
	CashRegister register1;	//Create instance of CashRegister class for use in the program
	ofstream receipt("Receipts.out"); //Open the output file for writing

	cout << "Welcome to the Cash Register program.\n\n";

	cout << "Now loading inventory information.  Please wait...\n";

	//If the CashRegister object was successfully initialized with the input file,
	//proceed to create a new customer order.
	if (register1.initialize("Invent.dat"))
	{
		cout << "Done.\n\n";

		cout << "Creating new customer order.\n\n";
		register1.createOrder(receipt);

		cout << endl << "Thank you for using this program!" << endl;

		receipt.close(); //Close the output file.
	}

	//If the CashRegister object could not be successfully initialized with the input file,
	//terminate the program with an error message.
	else
	{
		cout << "Error: Terminating program.\n\n";
	}

	system("pause");
	return 0;
}