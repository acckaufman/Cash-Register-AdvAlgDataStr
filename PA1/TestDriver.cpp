//Amanda Kaufman
//Programming Assignment 1
//CISS 350A
//This program functions as a cash register, processing a customer's order for an employee.

#include "CashRegister.h"

int main()
{
	char again = 'n';			//Ask the user if they want to create another order (y/n)
	CashRegister testRegister;	//Create instance of CashRegister class for use in the program
	ofstream testOutput("TestOutput.dat");	//File for test output
	ofstream receipt("Receipts.out");		//File for receipt output

	cout << "Welcome to the Cash Register program.\n\n";

	//#######################################################################################
	//initialize() function tests.															#
	//#######################################################################################

	testOutput << "initialize Test #1: Valid inventory file.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Invent.dat");
	testOutput << "Done.\n\n";
	
	testOutput << "initialize Test #2: Nonexistent inventory file.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Nonexistent_File.dat");
	testOutput << "Done.\n\n";

	testOutput << "initialize Test #3: Empty inventory file.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Test_InventoryEmpty.dat");
	testOutput << "Done.\n\n";

	testOutput << "initialize Test #4: Inventory file starts with 0.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Test_InventoryZeroStart.dat");
	testOutput << "Done.\n\n";

	testOutput << "initialize Test #5: Inventory file with duplicate product number.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Test_InventoryDuplicatePN.dat");
	testOutput << "Done.\n\n";

	testOutput << "initialize Test #6: Inventory file with too many items.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Test_InventoryTooFull.dat");
	testOutput << "Done.\n\n";

	testOutput << "initialize Test #7: Inventory file half full.\n";
	testOutput << "Now loading inventory information.  Please wait...\n";
	testRegister.initialize("Test_InventoryHalfFull.dat");
	testOutput << "Done.\n\n";

	system("pause");

	//#######################################################################################
	//createOrder() function tests.															#
	//#######################################################################################

	testOutput << "createOrder Test #1: Valid product number in inventory\n"
			   << "and valid quantity.";
	testOutput << "Product number: 11312.  Quantity: 2.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #2: Valid product number not in inventory\n"
		<< "and valid quantity.";
	testOutput << "Product number: 11111.  Quantity: 2.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #3: Invalid negative product number\n"
		<< "and valid quantity.";
	testOutput << "Product number: -11312.  Quantity: 2.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #4: Invalid product number over five digits\n"
		<< "and valid quantity.";
	testOutput << "Product number: 113125.  Quantity: 2.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #6: Valid product number in inventory\n"
		<< "and invalid negative quantity.";
	testOutput << "Product number: 11312.  Quantity: -2.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #7: Valid product number in inventory\n"
		<< "and invalid quantity over max.";
	testOutput << "Product number: 11312.  Quantity: 200.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	testOutput << "createOrder Test #8: Valid product number in inventory\n"
		<< "and invalid zero quantity.";
	testOutput << "Product number: 11312.  Quantity: 0.\n";
	testRegister.createOrder(receipt);
	testOutput << "Done.\n\n";

	system("pause");

	//#######################################################################################
	//getProduct() function tests.															#
	//#######################################################################################

	testOutput << "getProduct Test #1: Valid index of 5.\n";
	testRegister.getProduct(5);
	testOutput << "Done.\n\n";

	testOutput << "getProduct Test #2: Invalid index of -3.\n";
	testRegister.getProduct(-3);
	testOutput << "Done.\n\n";

	testOutput << "getProduct Test #3: Invalid index of 150.\n";
	testRegister.getProduct(150);
	testOutput << "Done.\n\n";

	system("pause");


	

	receipt.close();

	//while (again == 'y' || again == 'Y')
	//{

	//}

	system("pause");
	return 0;
}