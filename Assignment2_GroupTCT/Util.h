enum ERROR {
	invalidInput,
	duplicateID,
	invalidToPromote,
};

class Util {
private:
public:
	

	static string removeWhiteSpace(string text) {
		int lastIndex, firstIndex;
		for (lastIndex = text.length() - 1; lastIndex > 0; lastIndex--) {
			if (!(text[lastIndex] == ' ') && !(text[lastIndex] == '\t')) {
				break;
			}
		}
		for (firstIndex = 0; firstIndex < lastIndex; ++firstIndex) {
			if (!(text[firstIndex] == ' ') && !(text[firstIndex] == '\t')) {
				break;
			}
		}
		string newString;
		for (int i = firstIndex; i <= lastIndex; ++i) {
			newString += text[i];
		}
		return newString;
	}

	static void getInfo(string listOfInfo[], string* info) {
		int lastComma;
		for (int i = 5; i > 0; --i) {
			lastComma = (*info).find_last_of(",");
			listOfInfo[i] = (*info).substr(lastComma + 1);
			(*info).erase(lastComma, (*info).length());
		}
		listOfInfo[0] = *info;
	}

	static string trunkateFloat(float number) {
		string trunkatedNumber = to_string(number);
		int decimal = trunkatedNumber.find_last_of(".");
		if (decimal != -1) {
			trunkatedNumber.erase(decimal + 3,trunkatedNumber.length());
		}
		return trunkatedNumber;
	}

	static void errorDisplaying(int error) {
		switch (error) {
		case invalidInput:
			cout << "Invalid input." << endl;
			break;
		case duplicateID:
			cout << "This ID already exists" << endl;
			break;
		case invalidToPromote:
			cout << "This account hasn't returned enough books to be promoted" << endl;
			break;
		}
	}

	static void getcID(string* cID) {
		cout << endl << "Enter Customer ID: ";
		getline(cin, *cID);
		*cID = Util::removeWhiteSpace(*cID);
	}

	static void getiID(string* iID) {
		cout << endl << "Enter Item ID: ";
		getline(cin, *iID);
		*iID = Util::removeWhiteSpace(*iID);
	}
};

