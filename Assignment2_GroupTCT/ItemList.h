class ItemList
{
private:
	ItemNode *firstItem = NULL;
	DVDAndRecordsNode *firstDVDAndRecordsItem = NULL;
	int noOfItems = 0;

	void getRentalType(string* type) {
		getline(cin, *type);
		*type = Util::removeWhiteSpace(*type);
		while (type->compare("1") != 0 && type->compare("2") != 0 && type->compare("3") != 0) {
			Util::errorDisplaying(invalidInput);
			cout << "Enter rental type: " << endl;
			getline(cin, *type);
		}
		if (type->compare("1") == 0) { *type = "DVD"; }
		else if (type->compare("2") == 0) { *type = "Game"; }
		else { *type = "Records"; }
	}

	void getGenre(string* type) {
		getline(cin, *type);
		*type = Util::removeWhiteSpace(*type);
		while (type->compare("1") != 0 && type->compare("2") != 0 && type->compare("3") != 0 && type->compare("4") != 0) {
			Util::errorDisplaying(invalidInput);
			cout << "Enter genre type: " << endl;
			getline(cin, *type);
		}
		if (type->compare("1") == 0) { *type = "Action"; }
		else if (type->compare("2") == 0) { *type = "Horror"; }
		else if (type->compare("3") == 0) { *type = "Drama"; }
		else { *type = "Comedy"; }
	}

	void getItemID(string *ID) {
		getline(cin, *ID);
		Util::removeWhiteSpace(*ID);
		while (!validateNewID(*ID))
		{

		}
	}

	bool validateNewID(string ID) {
		if (!validateID(ID)) {
			Util::errorDisplaying(invalidInput);
			return false;
		}
		else if (isDuplicateID(ID)) {
			Util::errorDisplaying(duplicateID);
			return false;
		}
		else {
			return true;
		}

	}

	bool validateID(string ID) {
		if (ID.length() == 9) {
			if (ID[0] == 'I' && ID[4]) {
				for (int i = 1; i <= 3; ++i) {
					if (isdigit(ID[i]) == 0) {
						return false;
					}
				}
				for (int i = 5; i < 9; i++)
				{
					if (!isdigit(ID[i])) {
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}

	bool isDuplicateID(string iID) {
		if (noOfItems == 0) {
			return false;
		}
		else {
			DVDAndRecordsNode* item = searchDVDAndRecords(iID);
			if (item != NULL && item->getItem()->iID.compare(iID) == 0) {
				return true;
			}
			else {
				ItemNode* item = searchItem(iID);
				if (item != NULL && item->getItem()->iID.compare(iID) == 0) {
					return true;
				}
				else { return false; }
			}
		}
	}

	bool compareInfo(ItemNode* customer, string info, int field) {
		switch (field) {
		case title:
			return (*customer->getItem()).getTitle().compare(info) == 0;
			break;
		case ID:
			return (*customer->getItem()).iID.compare(info) == 0;
			break;
		case noOfCopies:
			return (*customer->getItem()).getNoOfCopies() == 0;
			break;
		case all:
			return true;
			break;
		default:
			return false;
		}
	}

	bool compareInfo(DVDAndRecordsNode* customer, string info, int field) {
		switch (field) {
		case title:
			return (*customer->getItem()).getTitle().compare(info) == 0;
			break;
		case ID:
			return (*customer->getItem()).iID.compare(info) == 0;
			break;
		case noOfCopies:
			return (*customer->getItem()).getNoOfCopies() == 0;
			break;
		case all:
			return true;
			break;
		default:
			return false;
		}
	}

	void getMatchedItem(string info, int field, int* count, string* itemInfo) {
		ItemNode* current = this->firstItem;
		while (current != NULL) {
			if (compareInfo(current, info, field)) {
				++*count;
				*itemInfo = current->getItem()->getInfo();
				++itemInfo;
			}
			current = (ItemNode*)current->getNext();
		}
	};

	void getMatchedDVDAndRecordsItem(string info, int field, int* count, string* itemInfo) {
		DVDAndRecordsNode* current = this->firstDVDAndRecordsItem;
		while (current != NULL) {
			if (compareInfo(current, info, field)) {
				++*count;
				*itemInfo = current->getItem()->getInfo();
				++itemInfo;
			}
			current = (DVDAndRecordsNode*)current->getNext();
		}
	}


public:
	ItemList() {};
	~ItemList() {};

	void displayItemList(string info, int field) {
		string* itemInfo = new string[this->noOfItems];
		string* p = itemInfo;
		if (this->noOfItems == 0) {
			cout << "No item found" << endl;
		}
		else {
			int countItem = 0;
			int countDVDAndRecords = 0;
			int matchedItems = 0;
			getMatchedItem(info, field, &countItem, itemInfo);
			getMatchedDVDAndRecordsItem(info, field, &countDVDAndRecords, itemInfo + countItem);
			matchedItems = countItem + countDVDAndRecords;
			if (matchedItems == 0) {
				cout << "No item found" << endl;
			}
			else {
				cout << "List of matched items (iID/title/rentalType/loanType/noOfCopies/rentalFee/rentalStatus/genre(optional))" << endl;
				if (matchedItems == 1) {
					cout << *itemInfo << endl;
				}
				else { displaySortedItemInfo(itemInfo, matchedItems); }
			}
		}
	}

	void displaySortedItemInfo(string* itemInfo, int matchedItems) {
		string iTitle1, iTitle2;
		string temp;
		for (int i = matchedItems - 1; i > 0; --i) {
			for (int j = 0; j < i; ++j) {
				iTitle1 = (*(itemInfo + j)).substr(0, 9);
				iTitle2 = (*(itemInfo + j + 1)).substr(0, 9);
				if (iTitle1.compare(iTitle2) > 0) {
					temp = *(itemInfo + j);
					*(itemInfo + j) = *(itemInfo + j + 1);
					*(itemInfo + j + 1) = temp;
				}
			}
		}
		for (int i = 0; i < matchedItems; ++i) {
			cout << *(itemInfo + i) << endl;
		}
	}

	ItemNode* searchItem(string iID) {
		ItemNode* current = this->firstItem;
		while (current != NULL)
		{
			if (current->getItem()->iID.compare(iID) == 0) {
				break;
			}
			else {
				current = (ItemNode*)current->getNext();
			}
		} return current;
	}

	DVDAndRecordsNode* searchDVDAndRecords(string iID) {
		DVDAndRecordsNode* current = this->firstDVDAndRecordsItem;
		while (current != NULL)
		{
			if (current->getItem()->iID.compare(iID) == 0) {
				break;
			}
			else {
				current = (DVDAndRecordsNode*)current->getNext();
			}
		}
		return current;
	}

	void rentItem(string iID) {
		ItemNode* itemReturned = searchItem(iID);
		if (itemReturned != NULL && itemReturned->getItem()->iID.compare(iID) == 0) {
			itemReturned->getItem()->rentItem();
		}
		else {
			DVDAndRecordsNode* DVDAndRecordReturned = searchDVDAndRecords(iID);
			if (DVDAndRecordReturned != NULL && DVDAndRecordReturned->getItem()->iID.compare(iID) == 0) {
				DVDAndRecordReturned->getItem()->rentItem();
			}
			else {
				cout << "No item found" << endl;
			}
		}
	}

	void returnItem(string iID) {
		ItemNode* itemReturned = searchItem(iID);
		if (itemReturned != NULL && itemReturned->getItem()->iID.compare(iID) == 0) {
			itemReturned->getItem()->returnItem();
		}
		else {
			DVDAndRecordsNode* DVDAndRecordReturned = searchDVDAndRecords(iID);
			if (DVDAndRecordReturned != NULL && DVDAndRecordReturned->getItem()->iID.compare(iID) == 0) {
				DVDAndRecordReturned->getItem()->returnItem();
			}
		}
	}

	void addItem(Item item) {
		if (this->firstItem == NULL) {
			this->firstItem = new ItemNode(item);
		}
		else {
			ItemNode* current = this->firstItem;
			ItemNode* newItem = new ItemNode(item);
			while (current->getNext() != NULL) {
				current = (ItemNode*)current->getNext();
			}
			current->setNext(newItem);
		}
		++this->noOfItems;
	}

	void addItem(DVDAndRecords item) {
		if (this->firstDVDAndRecordsItem == NULL) {
			this->firstDVDAndRecordsItem = new DVDAndRecordsNode(item);
		}
		else {
			DVDAndRecordsNode* current = this->firstDVDAndRecordsItem;
			DVDAndRecordsNode* newItem = new DVDAndRecordsNode(item);
			while (current->getNext() != NULL) {
				current = (DVDAndRecordsNode*)current->getNext();
			}
			current->setNext(newItem);
		}
		++this->noOfItems;
	}

	void deleteItem() {
		string iID;
		Util::getiID(&iID);
		ItemNode* itemReturned = searchItem(iID);
		if (itemReturned != NULL && itemReturned->getItem()->iID.compare(iID) == 0) {
			itemReturned->getItem()->deleteAllCopies();
			cout << "Successfully deleted" << endl;
		}
		else {
			DVDAndRecordsNode* deleteItemNode = searchDVDAndRecords(iID);
			if (deleteItemNode != NULL && deleteItemNode->getItem()->iID.compare(iID) == 0) {
				deleteItemNode->getItem()->deleteAllCopies();
				cout << "Successfully deleted" << endl;
			}
			else {
				cout << "No item found" << endl;
			}
		}
	}

	void addNewItem() {
		string info[7];
		cout << endl << "Enter ID as format Ixxx-xxxx (xxx-xxxx is unique code of 7 digits): ";
		getItemID(&info[0]);
		cout << endl << "Enter title: ";
		getline(cin, info[1]);
		info[1] = Util::removeWhiteSpace(info[1]);
		cout << endl << "Enter rental type (enter a number): " << endl << "1. DVD" << endl << "2. Game" << endl << "3. Records" << endl;
		getRentalType(&info[2]);
		cout << endl << "Enter loan type (enter a number): " << endl << "1. 2-day loan" << endl << "2. 1-week loan" << endl;
		Item::setLoanType(&info[3]);
		cout << endl << "Enter number of copies: ";
		getline(cin, info[4]);
		info[4] = Util::removeWhiteSpace(info[4]);
		cout << endl << "Enter fee: ";
		getline(cin, info[5]);
		info[5] = Util::removeWhiteSpace(info[5]);
		if (info[2].compare("DVD") == 0) {
			cout << endl << "Enter genre (enter a number): " << endl << "1. Action" << endl << "2. Horror" << endl << "3. Drama" << endl << "4. Comedy" << endl;
			getGenre(&info[6]);
			DVDAndRecords newItem(info[0], info[1], info[2], info[3], info[4], info[5],info[6]);
			addItem(newItem);
		}
		else if (info[2].compare("Game") == 0) {
			Item newItem(info[0], info[1], info[2], info[3], info[4], info[5]);
			addItem(newItem);
		}
		else if (info[2].compare("Records") == 0) {
			cout << endl << "Enter genre (enter a number): " << endl << "1. Action" << endl << "2. Horror" << endl << "3. Drama" << "4. Comedy" << endl;
			getGenre(&info[6]);
			DVDAndRecords newItem(info[0], info[1], info[2], info[3], info[4], info[5], info[6]);
			addItem(newItem);
		}
		cout << "Successfully added" << endl;
	}

	void editItem() {
		string iID;
		Util::getiID(&iID);
		ItemNode* editedItem = searchItem(iID);
		if (editedItem != NULL && editedItem->getItem()->iID.compare(iID) == 0) {
			editedItem->getItem()->editItem();
			cout << "Successfully editted" << endl;
		}
		else {
			DVDAndRecordsNode* editedDVDAndRecords = searchDVDAndRecords(iID);
			if (editedDVDAndRecords != NULL && editedDVDAndRecords->getItem()->iID.compare(iID) == 0) {
				editedDVDAndRecords->getItem()->editItem();
				cout << "Successfully editted" << endl;
			}
			else {
				cout << "Item not found" << endl;
			}
		}
	}
};
