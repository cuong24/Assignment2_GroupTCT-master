enum findingField {
	name,
	ID,
	type,
	all,
	title,
	noOfCopies,
	promote,
};

class CustomerList
{
private:
	VIPCustomerNode *firstVIPCustomer = NULL;
	RegularCustomerNode *firstRegularCustomer = NULL;
	GuestCustomerNode *firstGuestCustomer = NULL;

	int noOfCustomers = 0;

	bool compareInfo(VIPCustomerNode* customer, string info, int field) {
		switch (field) {
		case name:
			return customer->getCustomer()->getName().compare(info) == 0;
			break;
		case ID:
			return customer->getCustomer()->cID.compare(info) == 0;
			break;
		case type:
			return customer->getCustomer()->getCustomerType().compare(info) == 0;
			break;
		case promote:
			return customer->getCustomer()->getNoOfRenturnedRentals() > 3;
			break;
		case all:
			return true;
			break;
		default:
			return false;
		}
	}

	bool compareInfo(RegularCustomerNode* customer, string info, int field) {
		switch (field) {
		case name:
			return customer->getCustomer()->getName().compare(info) == 0;
			break;
		case ID:
			return customer->getCustomer()->cID.compare(info) == 0;
			break;
		case type:
			return customer->getCustomer()->getCustomerType().compare(info) == 0;
			break;
		case promote:
			return customer->getCustomer()->getNoOfRenturnedRentals() > 3;
			break;
		case all:
			return true;
			break;
		default:
			return false;
		}
	}

	bool compareInfo(GuestCustomerNode* customer, string info, int field) {
		switch (field) {
		case name:
			return customer->getCustomer()->getName().compare(info) == 0;
			break;
		case ID:
			return customer->getCustomer()->cID.compare(info) == 0;
			break;
		case type:
			return customer->getCustomer()->getCustomerType().compare(info) == 0;
			break;
		case promote:
			return customer->getCustomer()->getNoOfRenturnedRentals() > 3;
			break;
		case all:
			return true;
			break;
		default:
			return false;
		}
	}

	void searchMatchedVIPInfo(string info, int field, int* count, string* customerInfo) {
		VIPCustomerNode* current = this->firstVIPCustomer;
		while (current != NULL) {
			if (compareInfo(current, info, field)) {
				++*count;
				*customerInfo = current->getCustomer()->getInfo();
				++customerInfo;
			}
			current = (VIPCustomerNode*)current->getNext();
		}
	};

	void searchMatchedRegularInfo(string info, int field, int* count, string* customerInfo) {
		RegularCustomerNode* current = this->firstRegularCustomer;
		while (current != NULL) {
			if (compareInfo(current, info, field)) {
				++*count;
				*customerInfo = current->getCustomer()->getInfo();
				++customerInfo;
			}
			current = (RegularCustomerNode*)current->getNext();
		}
	};

	void searchMatchedGuestInfo(string info, int field, int* count, string* customerInfo) {
		GuestCustomerNode* current = this->firstGuestCustomer;
		while (current != NULL) {
			if (compareInfo(current, info, field)) {
				++*count;
				*customerInfo = current->getCustomer()->getInfo();
				++customerInfo;
			}
			current = (GuestCustomerNode*)current->getNext();
		}
	};

	void deleteGuestCustomer(string cID) {
		GuestCustomerNode* current = this->firstGuestCustomer;
		GuestCustomerNode* deleteNode = searchGuest(cID);
		if (this->firstGuestCustomer != deleteNode) {
			while (current->getNext() != deleteNode) {
				current = (GuestCustomerNode*)current->getNext();
			}
			current->setNext(deleteNode->getNext());
			delete deleteNode;
		}
		else {
			this->firstGuestCustomer = (GuestCustomerNode*)current->getNext();
			delete current;
			current = NULL;
		}
	}

	void deleteRegularCustomer(string cID) {
		RegularCustomerNode* current = this->firstRegularCustomer;
		RegularCustomerNode* deleteNode = searchRegular(cID);
		if (this->firstRegularCustomer != deleteNode) {
			while (current->getNext() != deleteNode) {
				current = (RegularCustomerNode*)current->getNext();
			}
			current->setNext(deleteNode->getNext());
			delete deleteNode;
		}
		else {
			this->firstRegularCustomer = (RegularCustomerNode*)current->getNext();
			delete current;
			current = NULL;
		}
	}

	void deleteVIPCustomer(string cID) {
		VIPCustomerNode* current = this->firstVIPCustomer;
		VIPCustomerNode* deleteNode = searchVIP(cID);
		if (this->firstVIPCustomer != deleteNode) {
			while (current->getNext() != deleteNode) {
				current = (VIPCustomerNode*)current->getNext();
			}
			current->setNext(deleteNode->getNext());
			delete deleteNode;
		}
		else {
			this->firstVIPCustomer = (VIPCustomerNode*)current->getNext();
			delete current;
			current = NULL;
		}
	}

public:
	CustomerList() {};
	~CustomerList() {};

	bool isDuplicateID(string cID) {
		if (this->noOfCustomers == 0) {
			return false;
		} else {
			VIPCustomerNode* customer = searchVIP(cID);
			if (customer != NULL && customer->getCustomer()->cID.compare(cID) == 0) {
				return true;
			}
			else {
				RegularCustomerNode* regularReturner = searchRegular(cID);
				if (regularReturner != NULL && regularReturner->getCustomer()->cID.compare(cID) == 0) {
					return true;
				}
				else {
					GuestCustomerNode* guestRenterner = searchGuest(cID);
					if (guestRenterner != NULL && guestRenterner->getCustomer()->cID.compare(cID) == 0) {
						return true;
					}
					else { return false; }
				}
			}
		}
	}

	bool displayCustomer(string info, int field) {
		string* customerInfo = new string[this->noOfCustomers];
		string* p = customerInfo;
		if (this->noOfCustomers == 0) {
			cout << "No customer found" << endl;
			return false;
		} else {
			int countVIP = 0;
			int countRegular = 0;
			int countGuest = 0;
			int matchedCustomers = 0;
			searchMatchedVIPInfo(info, field, &countVIP, p);
			searchMatchedRegularInfo(info, field, &countRegular, p + countVIP);
			searchMatchedGuestInfo(info, field, &countGuest, p + countVIP + countRegular);
			matchedCustomers = countVIP + countRegular + countGuest;
			if (matchedCustomers == 0) {
				cout << "No customer found" << endl;
				return false;
			} else {
				cout << "List of matched customers (cID/name/address/phone/noOfRentals/customerType)" << endl;
				if (matchedCustomers == 1) {
					cout << *customerInfo << endl;
				} else { displaySortedCustomerInfo(customerInfo, matchedCustomers);
				}
				return true;
			}
		}
	}

	void displaySortedCustomerInfo(string* customerInfo, int matchedCustomers) {
		string cName1, cName2;
		string temp;
		for (int i = matchedCustomers - 1; i > 0; --i) {
			for (int j = 0; j < i; ++j) {
				cName1 = (*(customerInfo + j)).substr(0, 4);
				cName2 = (*(customerInfo + j + 1)).substr(0, 4);
				if (cName1.compare(cName2) > 0) {
					temp = *(customerInfo + j);
					*(customerInfo + j) = *(customerInfo + j + 1);
					*(customerInfo + j + 1) = temp;
				}
			}
		}
		for (int i = 0; i < matchedCustomers; ++i) {
			cout << *(customerInfo + i) << endl;
		}
	}

	bool rentItem(string cID, string iID, string loanType) {
		VIPCustomerNode* VIPReturner = searchVIP(cID);
		if (VIPReturner != NULL && VIPReturner->getCustomer()->cID.compare(cID) == 0) {
			VIPReturner->getCustomer()->rentAnItem(iID);
		}
		else {
			RegularCustomerNode* regularReturner = searchRegular(cID);
			if (regularReturner != NULL && regularReturner->getCustomer()->cID.compare(cID) == 0) {
				regularReturner->getCustomer()->rentAnItem(iID);
			}
			else {
				GuestCustomerNode* guestRenterner = searchGuest(cID);
				if (guestRenterner != NULL && guestRenterner->getCustomer()->cID.compare(cID) == 0) {
					return guestRenterner->getCustomer()->rentAnItem(iID, loanType);
				}
				else {
					cout << "No customer found" << endl;
					return false;
				}
			}
		}
		return true;
	}

	void promoteCustomer(string cID) {
		string info[6];
		int noOfCurrentReturnedRentals;
		string* rentalInfo;
		VIPCustomerNode* customer = searchVIP(cID);
		if (customer != NULL && customer->getCustomer()->cID.compare(cID) == 0) {
			cout << "VIP customer can not be upgraded anymore";
		} else {
			RegularCustomerNode* regularCustomer = searchRegular(cID);
			if (regularCustomer != NULL && regularCustomer->getCustomer()->cID.compare(cID) == 0) {
				if (regularCustomer->getCustomer()->getNoOfRenturnedRentals() > 3) {
					string customerInfo = regularCustomer->getCustomer()->getInfo();
					Util::getInfo(info, &customerInfo);
					noOfCurrentReturnedRentals = regularCustomer->getCustomer()->getNoOfRenturnedRentals();
					VIPCustomer upgradedCustomer(info[0], info[1], info[2], info[3], stoi(info[4]), noOfCurrentReturnedRentals);
					rentalInfo = new string[upgradedCustomer.getNoOfRentals()];
					regularCustomer->getCustomer()->getFullRentals(rentalInfo);
					upgradedCustomer.updateRental(rentalInfo);
					addCustomer(&upgradedCustomer);
					deleteRegularCustomer(cID);
					cout << "Successfully upgraded" << endl;
				} else { cout << "Return more items to be promoted" << endl; }
			} else {
				GuestCustomerNode* guestCustomer = searchGuest(cID);
				if (guestCustomer != NULL && guestCustomer->getCustomer()->cID.compare(cID) == 0) {
					if (guestCustomer->getCustomer()->getNoOfRenturnedRentals() > 3) {
						string customerInfo = guestCustomer->getCustomer()->getInfo();
						Util::getInfo(info, &customerInfo);
						noOfCurrentReturnedRentals = guestCustomer->getCustomer()->getNoOfRenturnedRentals();
						RegularCustomer upgradedCustomer(info[0], info[1], info[2], info[3], stoi(info[4]), noOfCurrentReturnedRentals);
						rentalInfo = new string[upgradedCustomer.getNoOfRentals()];
						guestCustomer->getCustomer()->getFullRentals(rentalInfo);
						upgradedCustomer.updateRental(rentalInfo);
						addCustomer(&upgradedCustomer);
						deleteGuestCustomer(cID);
						cout << "Successfully upgraded" << endl;
					} else { cout << "Return more items to be promoted" << endl; }
				} else { cout << "No customer found" << endl; }
			}
		}
	}

	void deleteCustomer() {
		string cID;
		Util::getcID(&cID);
		VIPCustomerNode* vipCustomer = searchVIP(cID);
		if (vipCustomer != NULL && vipCustomer->getCustomer()->cID.compare(cID) == 0) {
			deleteVIPCustomer(cID);
			cout << "Successfully deleted" << endl;
		}
		else {
			RegularCustomerNode* regularCustomer = searchRegular(cID);
			if (regularCustomer != NULL && regularCustomer->getCustomer()->cID.compare(cID) == 0) {
				deleteRegularCustomer(cID);
				cout << "Successfully deleted" << endl;
			}
			else {
				GuestCustomerNode* guestCustomer = searchGuest(cID);
				if (guestCustomer != NULL && guestCustomer->getCustomer()->cID.compare(cID) == 0) {
					deleteGuestCustomer(cID);
					cout << "Successfully deleted" << endl;
				}
				else {
					cout << "No customer found" << endl;
				}
			}
		}
	}

	VIPCustomerNode* searchVIP(string cID) {
		VIPCustomerNode* current = this->firstVIPCustomer;
		while (current != NULL)
		{
			if (current->getCustomer()->cID.compare(cID) == 0) {
				break;
			}
			else {
				current = (VIPCustomerNode*)current->getNext();
			}
		} return current;
	}

	RegularCustomerNode* searchRegular(string cID) {
		RegularCustomerNode* current = this->firstRegularCustomer;
		while (current != NULL)
		{
			if (current->getCustomer()->cID.compare(cID) == 0) {
				break;
			}
			else {
				current = (RegularCustomerNode*)current->getNext();
			}
		}
		return current;
	}

	GuestCustomerNode* searchGuest(string cID) {
		GuestCustomerNode* current = this->firstGuestCustomer;
		while (current != NULL)
		{
			if (current->getCustomer()->cID.compare(cID) == 0) {
				break;
			}
			else {
				current = (GuestCustomerNode*)current->getNext();
			}
		}
		return current;
	}

	bool returnItem(string cID, string iID) {
		VIPCustomerNode* VIPReturner = searchVIP(cID);
		if (VIPReturner != NULL && VIPReturner->getCustomer()->cID.compare(cID) == 0) {
			VIPReturner->getCustomer()->returnItem(iID);
		}
		else {
			RegularCustomerNode* regularReturner = searchRegular(cID);
			if (regularReturner != NULL && regularReturner->getCustomer()->cID.compare(cID) == 0) {
				regularReturner->getCustomer()->returnItem(iID);
			}
			else {
				GuestCustomerNode* guestRenterner = searchGuest(cID);
				if (guestRenterner != NULL && guestRenterner->getCustomer()->cID.compare(cID) == 0) {
					guestRenterner->getCustomer()->returnItem(iID);
				}
				else {
					cout << "No customer found" << endl;
					return false;
				}
			}
		}
		return true;
	}

	void addCustomer(VIPCustomer* customer) {
		if (this->firstVIPCustomer == NULL) {
			this->firstVIPCustomer = new VIPCustomerNode(*customer);
		}
		else {
			VIPCustomerNode* current = this->firstVIPCustomer;
			VIPCustomerNode* newCustomer = new VIPCustomerNode(*customer);
			while (current->getNext() != NULL) {
				current = (VIPCustomerNode*)current->getNext();
			}
			current->setNext(newCustomer);
		}
		++this->noOfCustomers;
	}

	void addCustomer(RegularCustomer* customer) {
		if (this->firstRegularCustomer == NULL) {
			this->firstRegularCustomer = new RegularCustomerNode(*customer);
		}
		else {
			RegularCustomerNode* current = this->firstRegularCustomer;
			RegularCustomerNode* newCustomer = new RegularCustomerNode(*customer);
			while (current->getNext() != NULL) {
				current = (RegularCustomerNode*)current->getNext();
			}
			current->setNext(newCustomer);
		}
		++this->noOfCustomers;
	}

	void addCustomer(GuestCustomer* customer) {
		if (this->firstGuestCustomer == NULL) {
			this->firstGuestCustomer = new GuestCustomerNode(*customer);
		}
		else {
			GuestCustomerNode* current = this->firstGuestCustomer;
			GuestCustomerNode* newCustomer = new GuestCustomerNode(*customer);
			while (current->getNext() != NULL) {
				current = (GuestCustomerNode*)current->getNext();
			}
			current->setNext(newCustomer);
		}
		++this->noOfCustomers;
	}

	void rentItem(Customer customer) {
	}
};
