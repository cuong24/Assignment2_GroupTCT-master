class DVDAndRecordsNode : public Node {
private:
	DVDAndRecords item;
public:
	DVDAndRecordsNode(DVDAndRecords newItem, Node* nextNode) {
		this->item = newItem;
		setNext(nextNode);
	};

	DVDAndRecordsNode(DVDAndRecords newItem) {
		this->item = newItem;
		setNext(NULL);
	};

	DVDAndRecords* getItem() {
		return &this->item;
	};

	void setCustomer(DVDAndRecords newItem) {
		this->item = newItem;
	};
};
