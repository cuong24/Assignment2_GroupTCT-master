// asm2_groupTCT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Util.h"
#include "Node.h"
#include "Item.h"
#include "ItemNode.h"
#include "DVDAndRecordsNode.h"
#include "RentalNode.h"
#include "Customer.h"
#include "VIPCustomerNode.h"
#include "RegularCustomerNode.h"
#include "GuestCustomerNode.h"
#include "CustomerList.h"
#include "ItemList.h"

enum option {
	customer,
	item,
	itemOrCustomer,
	newEditCustomer,
	newEditItem,
};

void openFile(fstream* itemf, fstream* customerf);
void loadFileToLists(CustomerList* customerList, fstream* customerf, ItemList* itemList, fstream* itemf);
void uploadCustomer(fstream* customerf, string info[], CustomerList* customerList);
void createCustomer(string info[], CustomerList* customerList, fstream* customerf);
void updateCustomerRentals(Customer* newCustomer, fstream* customerf, string* rentalInfo);
void uploadItem(fstream* itemf, string info[], ItemList* itemList);
void getInfoItem(string info[], string itemInfo);
void createItem(string info[], ItemList* itemList);
void displayGroupOfCustomer(CustomerList* customerList);
void searchItemOrCustomer(CustomerList* customerList, ItemList* itemList);
void searchCustomer(CustomerList* customerList);
void searchItem(ItemList* itemList);
string getOption(int option);
void getIDs(string* cID, string*iID, CustomerList* customerList);
void rentItem(CustomerList* customerList, ItemList* itemList);
void returnItem(CustomerList* customerList, ItemList* itemList);
void addEditDeleteCustomer(CustomerList* customerList);
void addNewCustomer(CustomerList* customerList);
void getCustomerType(string* type);
void getPhone(string* phone);
bool validatePhone(string phone);
void getID(string *ID, CustomerList* customerList);
bool validateNewID(string ID, CustomerList* customerList);
bool validateID(string ID);
void addEditDeleteItem(ItemList* itemList);
void displayMenu();
void getFunction(string* function);
bool validateFunction(string function);
bool isNumber(string function);
void exitMessage();
void closeFile(fstream* itemf, fstream* customerf);

bool validateNewID(string ID, CustomerList* customerList) {
	if (!validateID(ID)) {
		Util::errorDisplaying(invalidInput);
		return false;
	}
	else if (customerList->isDuplicateID(ID)) {
		Util::errorDisplaying(duplicateID);
		return false;
	}
	else {
		return true;
	}

}

bool validateID(string ID) {
	if (ID.length() == 4) {
		if (ID[0] == 'C') {
			for (int i = 1; i <= 3; ++i) {
				if (isdigit(ID[i]) == 0) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

void openFile(fstream* itemf, fstream* customerf) {
	(*itemf).open("items.txt", ios::in || ios::out);
	(*customerf).open("customers.txt", ios::in || ios::out);
	if (!*itemf || !*customerf) {
		cerr << "Either file items.txt or file customers.txt is missing or both. Please include both files to run the program.";
		exit(-1);
	}
}

void loadFileToLists(CustomerList* customerList, fstream* customerf, ItemList* itemList, fstream* itemf) {
	string customerInfo[6];
	string itemInfo[7];

	uploadCustomer(customerf, customerInfo, customerList);
	uploadItem(itemf, itemInfo, itemList);
}

void uploadCustomer(fstream* customerf, string info[], CustomerList* customerList) {
	while (!(*customerf).eof()) {
		string customerInfo;
		getline(*customerf, customerInfo);
		Util::getInfo(info, &customerInfo);
		createCustomer(info, customerList, customerf);
	}
}

void createCustomer(string info[], CustomerList* customerList, fstream* customerf) {
	string* rentalInfo;
	int noOfRentals;
	if (info[5].compare("VIP") == 0) {
		VIPCustomer newCustomer(info[0], info[1], info[2], info[3], stoi(info[4]));
		noOfRentals = newCustomer.getNoOfRentals();
		rentalInfo = new string[noOfRentals];
		updateCustomerRentals(&newCustomer, customerf, rentalInfo);
		customerList->addCustomer(&newCustomer);
	}
	else if (info[5].compare("Regular") == 0) {
		RegularCustomer newCustomer(info[0], info[1], info[2], info[3], stoi(info[4]));
		noOfRentals = newCustomer.getNoOfRentals();
		rentalInfo = new string[noOfRentals];
		updateCustomerRentals(&newCustomer, customerf, rentalInfo);
		customerList->addCustomer(&newCustomer);
	}
	else if (info[5].compare("Guest") == 0) {
		GuestCustomer newCustomer(info[0], info[1], info[2], info[3], stoi(info[4]));
		noOfRentals = newCustomer.getNoOfRentals();
		rentalInfo = new string[noOfRentals];
		updateCustomerRentals(&newCustomer, customerf, rentalInfo);
		customerList->addCustomer(&newCustomer);
	}
}

void updateCustomerRentals(Customer* newCustomer, fstream* customerf, string* rentalInfo) {
	int noOfRentals = newCustomer->getNoOfRentals();
	for (int i = 0; i < noOfRentals; ++i) {
		getline(*customerf, *(rentalInfo + i));
	}
	newCustomer->updateRental(rentalInfo);
}

void uploadItem(fstream* itemf, string info[], ItemList* itemList) {
	while (!(*itemf).eof()) {
		string itemInfo;
		getline(*itemf, itemInfo);
		getInfoItem(info, itemInfo);
		createItem(info, itemList);

	}
}

void getInfoItem(string info[], string itemInfo) {
	Util::getInfo(info, &itemInfo);
	int lastComma;
	size_t found = itemInfo.find(",");
	if (found != std::string::npos) {
		lastComma = itemInfo.find_last_of(",");
		info[0] = itemInfo.substr(lastComma + 1);
		itemInfo.erase(lastComma, itemInfo.length());
		info[6] = itemInfo;
	}
	else {
		info[6] = "game";
	}
}

void createItem(string info[], ItemList* itemList) {
	if (info[6].compare("game") == 0) {
		Item newItem(info[0], info[1], info[2], info[3], info[4], info[5]);
		itemList->addItem(newItem);
	}
	else if (info[6].compare("game") != 0) {
		DVDAndRecords newItem(info[6], info[0], info[1], info[2], info[3], info[4], info[5]);
		itemList->addItem(newItem);
	}
}

void displayGroupOfCustomer(CustomerList* customerList) {
	string customerType;
	cout << "Customer type  (enter number):" << endl << "1. VIP" << endl << "2. Regular" << endl << "3. Guest" << endl;
	getline(cin, customerType);
	customerType = Util::removeWhiteSpace(customerType);
	if (isNumber(customerType)) {
		switch (stoi(customerType)) {
		case 1:
			customerList->displayCustomer("VIP", type);
			break;
		case 2:
			customerList->displayCustomer("Regular", type);
			break;
		case 3:
			customerList->displayCustomer("Guest", type);
			break;
		default:
			Util::errorDisplaying(invalidInput);
			break;
		}
	}
	else {
		Util::errorDisplaying(invalidInput);
	}
}

void searchItemOrCustomer(CustomerList* customerList, ItemList* itemList) {
	string searchFor = getOption(itemOrCustomer);
	if (isNumber(searchFor) && (stoi(searchFor) == 1 || stoi(searchFor) == 2)) {
		switch (stoi(searchFor)) {
		case 1:
			searchItem(itemList);
			break;
		case 2:
			searchCustomer(customerList);
			break;
		default:
			Util::errorDisplaying(invalidInput);
		}
	}
	else {
		Util::errorDisplaying(invalidInput);
	}

}

void searchCustomer(CustomerList* customerList) {
	cout << endl << "Full list of customer" << endl;
	customerList->displayCustomer("all", all);
	cout << endl;
	string searchBy = getOption(customer);
	if (isNumber(searchBy) && (stoi(searchBy) == 1 || stoi(searchBy) == 2)) {
		string info;
		cout << endl << "Enter information to search: ";
		getline(cin, info);
		info = Util::removeWhiteSpace(info);
		cout << endl;
		switch (stoi(searchBy)) {
		case 1:
			customerList->displayCustomer(info, name);
			break;
		case 2:
			customerList->displayCustomer(info, ID);
			break;
		default:
			Util::errorDisplaying(invalidInput);
		}
	}
	else {
		Util::errorDisplaying(invalidInput);
	}
}

void searchItem(ItemList* itemList) {
	cout << endl << "Full list of item" << endl;
	itemList->displayItemList("all", all);
	string searchBy = getOption(item);
	if (isNumber(searchBy) && (stoi(searchBy) == 1 || stoi(searchBy) == 2)) {
		string info;
		cout << endl << "Enter information to search: ";
		getline(cin, info);
		info = Util::removeWhiteSpace(info);
		cout << endl;
		switch (stoi(searchBy)) {
		case 1:
			itemList->displayItemList(info, title);
			break;
		case 2:
			itemList->displayItemList(info, ID);
			break;
		default:
			Util::errorDisplaying(invalidInput);
		}
	}
	else {
		Util::errorDisplaying(invalidInput);
	}
}

string getOption(int option) {
	string searchOption;
	switch (option) {
	case (item):
		cout << endl << "Search by (enter number): " << endl << "1. By title" << endl << "2. By ID" << endl;
		break;
	case (itemOrCustomer):
		cout << "Search for (enter a number): " << endl << "1. Search for item" << endl << "2. Search for customer" << endl;
		break;
	case (customer):
		cout << endl << "Search by (enter number): " << endl << "1. By name" << endl << "2. By ID" << endl;
		break;
	case (newEditCustomer):
		cout << endl << "Function (enter number):" << endl << "1. Add new customer" << endl << "2. Edit customer" << endl << "3. Delete customer" << endl;
		break;
	case (newEditItem):
		cout << endl << "Function (enter number):" << endl << "1. Add new item" << endl << "2. Edit item" << endl << "3. Delete item" << endl;
		break;
	default:
		Util::errorDisplaying(invalidInput);
	}
	getline(cin, searchOption);
	searchOption = Util::removeWhiteSpace(searchOption);
	return searchOption;
}



void getIDs(string* cID, string*iID, CustomerList* customerList) {
	Util::getcID(cID);
	VIPCustomerNode* VIPReturner = customerList->searchVIP(*cID);
	if (VIPReturner != NULL && VIPReturner->getCustomer()->cID.compare(*cID) == 0) {
		cout << "List of current rentals" << endl;
		VIPReturner->getCustomer()->displayRental();
	}
	else {
		RegularCustomerNode* regularReturner = customerList->searchRegular(*cID);
		if (regularReturner != NULL && regularReturner->getCustomer()->cID.compare(*cID) == 0) {
			cout << "List of current rentals" << endl;
			regularReturner->getCustomer()->displayRental();
		}
		else {
			GuestCustomerNode* guestRenterner = customerList->searchGuest(*cID);
			if (guestRenterner != NULL && guestRenterner->getCustomer()->cID.compare(*cID) == 0) {
				cout << "List of current rentals" << endl;
				guestRenterner->getCustomer()->displayRental();
			}
		}
	}
	Util::getiID(iID);
}

void rentItem(CustomerList* customerList, ItemList* itemList) {
	cout << "Full list of Item" << endl;
	itemList->displayItemList("all", all);
	cout << endl;
	cout << "Full list of customer" << endl;
	customerList->displayCustomer("all", all);
	cout << endl;
	string cID, iID;
	getIDs(&cID, &iID, customerList);
	ItemNode* itemRent = itemList->searchItem(iID);
	if (itemRent != NULL && itemRent->getItem()->iID.compare(iID) == 0) {
		if (itemRent->getItem()->getRentalStatus().compare("Available") == 0) {
			if (customerList->rentItem(cID, iID, itemRent->getItem()->getLoanType())) {
				itemList->rentItem(iID);
			}
		}
		else {
			cout << "Item out of stock" << endl;
		}
	}
	else {
		DVDAndRecordsNode* DVDAndRecordRent = itemList->searchDVDAndRecords(iID);
		if (DVDAndRecordRent != NULL && DVDAndRecordRent->getItem()->iID.compare(iID) == 0) {
			if (DVDAndRecordRent->getItem()->getRentalStatus().compare("Available") == 0) {
				if (customerList->rentItem(cID, iID, DVDAndRecordRent->getItem()->getLoanType())) {
					itemList->rentItem(iID);
				}
			}
			else {
				cout << "Item out of stock" << endl;
			}
		}
		else {
			cout << "No item found";
		}
	}
}

void returnItem(CustomerList* customerList, ItemList* itemList) {
	cout << "Full list of customer" << endl;
	customerList->displayCustomer("all", all);
	string cID, iID;
	getIDs(&cID, &iID, customerList);
	if (customerList->returnItem(cID, iID)) {
		itemList->returnItem(iID);
	}
}

void addEditDeleteCustomer(CustomerList* customerList) {
	cout << endl << "Full list of customer" << endl;
	customerList->displayCustomer("all", all);
	string function = getOption(newEditCustomer);
	if (isNumber(function) && (stoi(function) == 1 || stoi(function) == 2 || stoi(function) == 3)) {
		switch (stoi(function)) {
		case 1:
			addNewCustomer(customerList);
			break;
		case 2:
			break;
		case 3:
			customerList->deleteCustomer();
			break;
		default:
			Util::errorDisplaying(invalidInput);
			break;
		}
	}
	else { Util::errorDisplaying(invalidInput); }
}

void addNewCustomer(CustomerList* customerList) {
	string info[6];
	cout << endl << "Enter ID as format Cxxx (xxx is unique code of 3 digits): ";
	getID(&info[0], customerList);
	cout << endl << "Enter name: ";
	getline(cin, info[1]);
	cout << endl << "Enter address: ";
	getline(cin, info[2]);
	cout << endl << "Enter phone (include numbers only, from 5 - 15 numbers): ";
	getPhone(&info[3]);
	cout << endl << "Enter customer type (enter a number): " << endl << "1. VIP" << endl << "2. Regular" << endl << "3. Guest" << endl;
	getCustomerType(&info[5]);
	if (info[5].compare("VIP") == 0) {
		VIPCustomer newCustomer(info[0], info[1], info[2], info[3], 0);
		customerList->addCustomer(&newCustomer);
	}
	else if (info[5].compare("Regular") == 0) {
		RegularCustomer newCustomer(info[0], info[1], info[2], info[3], 0);
		customerList->addCustomer(&newCustomer);
	}
	else if (info[5].compare("Guest") == 0) {
		GuestCustomer newCustomer(info[0], info[1], info[2], info[3], 0);
		customerList->addCustomer(&newCustomer);
	}
}

void getCustomerType(string* type) {
	getline(cin, *type);
	Util::removeWhiteSpace(*type);
	while (type->compare("1") != 0 && type->compare("2") != 0 && type->compare("3") != 0) {
		Util::errorDisplaying(invalidInput);
		cout << "Enter customer type: " << endl;
		getline(cin, *type);
	}
	if (type->compare("1") == 0) {*type = "VIP";} 
	else if (type->compare("2") == 0) { *type = "Regular"; }
	else {*type = "Guest";}
}

void getPhone(string* phone) {
	getline(cin, *phone);
	Util::removeWhiteSpace(*phone);
	while (!validatePhone(*phone)) {
		cout << "Enter phone: ";
		getline(cin, *phone);
	}
}

bool validatePhone(string phone) {
	if (phone.length() > 15 || phone.length() < 5) {
		Util::errorDisplaying(invalidInput);
		return false;
	} else if (!isNumber(phone)) {
		Util::errorDisplaying(invalidInput);
		return false;
	} else { return true; }
}

void getID(string *ID, CustomerList* customerList) {
	getline(cin, *ID);
	Util::removeWhiteSpace(*ID);
	while (!validateNewID(*ID, customerList)) {
		cout << "Enter ID: ";
		getline(cin, *ID);
	}
}

void addEditDeleteItem(ItemList* itemList) {
	cout << endl << "Full list of item" << endl;
	itemList->displayItemList("all", all);
	cout << endl;
	string function = getOption(newEditItem);
	if (isNumber(function) && (stoi(function) == 1 || stoi(function) == 2) || stoi(function) == 3) {
		switch (stoi(function)) {
		case 1:
			itemList->addNewItem();
			break;
		case 2:
			itemList->editItem();
			break;
		case 3:
			itemList->deleteItem();
			break;
		default: 
			Util::errorDisplaying(invalidInput);
			break;
		}
	} else {Util::errorDisplaying(invalidInput);}
}

void promoteCustomer(CustomerList* customerList) {
	cout << "Full list of valid customer to be promoted (returned more than 3 items)" << endl;
	if (customerList->displayCustomer("promomte", promote)) {
		string cID;
		Util::getcID(&cID);
		customerList->promoteCustomer(cID);
	}
}

void displayMenu() {
	cout << "Welcome to Genie’s video store" << endl;
	cout << "Enter an option below." << endl;
	cout << "1. Add a new item, update or delete an existing item" << endl;
	cout << "2. Add new customer or update an existing customer" << endl;
	cout << "3. Promote an existing customer" << endl;
	cout << "4. Rent an item" << endl;
	cout << "5. Return an item" << endl;
	cout << "6. Display all items" << endl;
	cout << "7. Display out - of - stock items" << endl;
	cout << "8. Display all customers" << endl;
	cout << "9. Display group of customers" << endl;
	cout << "10. Search items or customers" << endl;
	cout << "Exit." << endl;
}

void getFunction(string* function) {
	cout << "Enter function's number: ";
	getline(cin, *function);
	*function = Util::removeWhiteSpace(*function);
	while (!validateFunction(*function)) {
		Util::errorDisplaying(invalidInput);
		cout << "Enter function's number: ";
		getline(cin, *function);
		*function = Util::removeWhiteSpace(*function);
	}
}

//Exit, 1->11
bool validateFunction(string function) {
	if (function.compare("Exit") == 0) {
		return true;
	}
	else {
		if (isNumber(function)) {
			if (1 <= stoi(function) && stoi(function) <= 10) {
				return true;
			}
		}
	}
	return false;
}

bool isNumber(string input) {
	if (input.length() < 1) {
		return false;
	}
	else {
		for (int i = 0; i < input.length(); ++i) {
			if (!isdigit(input[i])) {
				return false;
			}
		}
	}
	return true;
}

void performFunction(string function, CustomerList* customerList, ItemList *itemList) {
	cout << endl << "--------------------------------" << endl;
	if (function.compare("Exit") == 0) {
		exitMessage();
		exit(-1);
	}
	else {
		switch (stoi(function)) {
		case 1:
			addEditDeleteItem(itemList);
			break;
		case 2:
			addEditDeleteCustomer(customerList);
			break;
		case 3:
			promoteCustomer(customerList);
			break;
		case 4:
			rentItem(customerList, itemList);
			break;
		case 5:
			returnItem(customerList, itemList);
			break;
		case 6:
			itemList->displayItemList("all", all);
			break;
		case 7:
			itemList->displayItemList("0", noOfCopies);
			break;
		case 8:
			customerList->displayCustomer("all", all);
			break;
		case 9:
			displayGroupOfCustomer(customerList);
			break;
		case 10:
			searchItemOrCustomer(customerList, itemList);
			break;
		case 11: 
			itemList->deleteItem();
			break;
		}
	}
	cout << endl << "--------------------------------" << endl;
}

void exitMessage() {
	cout << "ASSIGNMENT 2 GROUP TCT" << endl;
	cout << "s3748840, s3748840@rmit.edu.vn, Cuong, Nguyen" << endl;
	cout << "s3757934, s3757934@rmit.edu.vn, Tien, Nguyen" << endl;
	cout << "s3747274, s3747274@rmit.edu.vn, Tam, Nguyen" << endl;
}

void closeFile(fstream* itemf, fstream* customerf) {
	if (itemf != NULL) {
		(*itemf).close();
	}
	if (customerf != NULL) {
		(*customerf).close();
	}
}

int main()
{
	CustomerList customerList;
	ItemList itemList;
	string function;
	fstream itemf;
	fstream customerf;

	openFile(&itemf, &customerf);
	loadFileToLists(&customerList, &customerf, &itemList, &itemf);

	do {
		displayMenu();
		getFunction(&function);
		performFunction(function, &customerList, &itemList);
	} while (true);

	closeFile(&itemf, &customerf);
	return 0;
}

