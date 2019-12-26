class RentalNode : public Node {
private:
	string ID;
public:
	RentalNode(string newRentalID, Node *nextNode) {
		this->ID = newRentalID;
		setNext(nextNode);
	};

	RentalNode(string newRentalID) {
		this->ID = newRentalID;
		setNext(NULL);
	};

	string getData() {
		return this->ID;
	};

	void setData(string newRentalID) {
		this->ID = newRentalID;
	};
};
