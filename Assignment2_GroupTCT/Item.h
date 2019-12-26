class Item
{
private:
	string title, rentalType, loanType, rentalStatus;
	string genre = "";
	float rentalFee = 0;
	int noOfCopies = 0;

public:
	string iID;

	Item() {};

	~Item() {};

	static void setLoanType(string* type) {
		getline(cin, *type);
		*type = Util::removeWhiteSpace(*type);
		while (type->compare("1") != 0 && type->compare("2") != 0) {
			Util::errorDisplaying(invalidInput);
			cout << "Enter loan type: " << endl;
			getline(cin, *type);
		}
		if (type->compare("1") == 0) { *type = "1-week"; }
		else { *type = "2-day"; }
	}

	Item(string iID, string title, string rentalType, string loanType, string noOfCopies, string fee) {
		this->iID = iID;
		this->title = title;
		this->rentalType = rentalType;
		this->loanType = loanType;
		this->noOfCopies = stoi(noOfCopies);
		this->rentalFee = stof(fee);
		if (noOfCopies.compare("0") == 0) {
			rentalStatus = "Borrowed";
		}
		else {
			rentalStatus = "Available";
		}
	}

	void rentItem() {
		if (rentalStatus == "Borrowed") {
			cout << "No more copies available" << endl;
		}
		else {
			--this->noOfCopies;
			if (this->noOfCopies == 0) {
				this->rentalStatus = "Borrowed";
			}
			else { this->rentalStatus = "Available"; }
		}
	}

	void returnItem() {
		if (this->noOfCopies == 0) {
			this->rentalStatus = "Available";
		}
		++this->noOfCopies;
	}

	string getBasicInfo() {
		return this->iID + "," + this->title + "," + this->rentalType + ","
			 + this->loanType + "," + to_string(this->noOfCopies)+ "," + Util::trunkateFloat(this->rentalFee) + "," + this->rentalStatus;
	}

	virtual string getInfo() {
		return getBasicInfo();
	}

	string getTitle() {
		return this->title;
	}

	int getNoOfCopies() {
		return this->noOfCopies;
	}

	string getLoanType() {
		return loanType;
	}

	string getRentalStatus() {
		return rentalStatus;
	}

	void deleteAllCopies(){
		this->noOfCopies = 0;
	}

	void editItem() {
		string newInfo;
		cout << endl << "Enter loan type (enter a number): " << endl << "1. 2-day loan" << endl << "2. 1-week loan" << endl;
		Item::setLoanType(&loanType);
		cout << endl << "Enter number of copies: ";
		getline(cin, newInfo);
		noOfCopies = stoi(Util::removeWhiteSpace(newInfo));
		cout << endl << "Enter fee: ";
		getline(cin, newInfo);
		rentalFee = stof(Util::removeWhiteSpace(newInfo));
	}
};

class DVDAndRecords : public Item
{
public:
	DVDAndRecords() {};
	~DVDAndRecords() {};
	string genre;

	DVDAndRecords(string ID, string title, string rentalType, string loanType, string numOfCopies, string fee, string genre) : Item(ID, title, rentalType, loanType, numOfCopies, fee) {
		this->genre = genre;
	}

	string getInfo() {
		return getBasicInfo() + "," + this->genre;
	}
};
