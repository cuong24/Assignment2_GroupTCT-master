class Customer {
private:
	string name, address, phone, customerType;
	int noOfRentals = 0;
	int noOfRentalsReturned = 0;
	RentalNode *firstRental = NULL;

	RentalNode* search(string iID) {
		RentalNode* current = this->firstRental;
		while (current != NULL)
		{
			if (current->getData().compare(iID) == 0)
				break;
			else
				current = (RentalNode*)current->getNext();
		}
		return current;
	}
public:
	string cID;

	Customer(string cID, string name, string address, string phone, int noOfRentals) {
		this->cID = cID;
		this->name = name;
		this->address = address;
		this->phone = phone;
		this->noOfRentals = noOfRentals;
	};

	Customer() {};

	~Customer() {};

	void rentItem(string iID) {
		if (this->firstRental == NULL) {
			this->firstRental = new RentalNode(iID);
		}
		else {
			RentalNode* current = this->firstRental;
			RentalNode* newRental = new RentalNode(iID);
			while (current->getNext() != NULL) {
				current = (RentalNode*)current->getNext();
			}
			current->setNext(newRental);
		}
		++this->noOfRentals;
	};

	virtual	void rentAnItem() {}

	void returnItem(string iID) {
		RentalNode* current = this->firstRental;
		RentalNode* deleteNode = search(iID);
		if (deleteNode == NULL || deleteNode->getData().compare(iID) != 0) {
			cout << "No item found" << endl;
		}
		else {
			++this->noOfRentalsReturned;
			--this->noOfRentals;
			cout << "Successfully returned!" << endl;
			if (this->firstRental != deleteNode) {
				while (current->getNext() != deleteNode) {
					current = (RentalNode*)current->getNext();
				}
				current->setNext(deleteNode->getNext());
				delete deleteNode;
			}
			else {
				this->firstRental = (RentalNode*)current->getNext();
				delete current;
				current = NULL;
			}
		}
	};

	void displayRental() {
		if (this->noOfRentals == 0) {
			cout << "No rentals" << endl;
		} else {
			RentalNode* current = this->firstRental;
			while (current->getNext() != NULL) {
				cout << current->getData() << endl;
				current = (RentalNode*)current->getNext();
			}
			cout << current->getData() << endl;
		}
	}

	void getFullRentals(string* rentalInfo) {
		RentalNode* current = this->firstRental;
		while (current != NULL) {
			*rentalInfo = current->getData();
			++rentalInfo;
			current = (RentalNode*)current->getNext();
		}
	}

	void updateRental(string* rentalInfo) {
		for (int i = 0; i < this->noOfRentals; ++i) {
			rentItem(*(rentalInfo + i));
			--this->noOfRentals;
		}
	}

	void setCustomerType(string type) {
		this->customerType = type;
	}

	void displayInfo() {
		cout << getInfo();
		displayRental();
	}

	string getInfo() {
		return this->cID + "," + this->name + "," + this->address + "," + this->phone + "," + to_string(noOfRentals) + "," + this->customerType;
	}

	string getName() {
		return this->name;
	}

	string getCustomerType() {
		return this->customerType;
	}

	int getNoOfRenturnedRentals() {
		return this->noOfRentalsReturned;
	}

	int getNoOfRentals() {
		return this->noOfRentals;
	};

	void setNoOfRentals(int noOfRentals) {
		this->noOfRentals = noOfRentals;
	}

	void resetNoOfRentalsReturned(int noOfRentalsReturned) {
		this->noOfRentalsReturned = noOfRentalsReturned - 4;
	}
};

class VIPCustomer : public Customer {
private:
	int rewardPoint = 100;

	void announceRentForFree() {
		cout << "Congratulation! You can rent 1 item for free!!" << endl;
		cout << "Do you want to rent this item for free?" << endl;
		cout << "Enter Y for Yes (anything else means cancelling)" << endl;
	}

	void usePoint() {
		this->rewardPoint -= 100;
	}

	void accumulatePoint() {
		this->rewardPoint += 10;
	}

public:
	VIPCustomer(string cID, string name, string address, string phone, int noOfRentals) : Customer(cID, name, address, phone, noOfRentals) {
		setCustomerType("VIP");
	};

	VIPCustomer(string cID, string name, string address, string phone, int noOfRentals, int noOfRentalsReturned) : Customer(cID, name, address, phone, noOfRentals) {
		setCustomerType("VIP");
		setNoOfRentals(noOfRentals);
		resetNoOfRentalsReturned(noOfRentalsReturned);
	};

	VIPCustomer() {};

	~VIPCustomer() {};

	void rentAnItem(string iID) {
		if (this->rewardPoint >= 100) {
			string confirmation;
			announceRentForFree();
			getline(cin, confirmation);
			confirmation = Util::removeWhiteSpace(confirmation);
			if (confirmation.compare("Y") == 0) {
				usePoint();			}
		}
		rentItem(iID);
		accumulatePoint();
		cout << "Successfully rented!" << endl;
	}
};

class RegularCustomer : public Customer {
public:
	RegularCustomer(string cID, string name, string address, string phone, int noOfRentals) : Customer(cID, name, address, phone, noOfRentals) {
		setCustomerType("Regular");
	};

	RegularCustomer(string cID, string name, string address, string phone, int noOfRentals, int noOfRentalsReturned) : Customer(cID, name, address, phone, noOfRentals) {
		setCustomerType("Regular");
		setNoOfRentals(noOfRentals);
		resetNoOfRentalsReturned(noOfRentalsReturned);
	};

	RegularCustomer() {};

	~RegularCustomer() {};

	void rentAnItem(string iID) {
		rentItem(iID);
		cout << "Successfully rented!" << endl;
	}
};

class GuestCustomer : public Customer {
public:
	GuestCustomer(string cID, string name, string address, string phone, int noOfRentals) : Customer(cID, name, address, phone, noOfRentals) {
		setCustomerType("Guest");
	};

	GuestCustomer() {};

	~GuestCustomer() {};

	bool rentAnItem(string iID, string loanType) {
		cout << loanType << endl;
		if (getNoOfRentals() == 2) {
			cout << "You have reached the maximum number of rentals. Upgrade to rent more" << endl;
			return false;
		}
		else if (loanType.compare("2-day") == 0) {
			cout << "Guest customer can not rent a 2-day item" << endl;
			return false;
		}
		else {
			rentItem(iID);
			cout << "Successfully rented!" << endl;
			return true;
		}
		return false;
	}
};
