class ItemNode : public Node {
private:
	Item item;
public:
	ItemNode(Item newItem, Node* nextNode) {
		this->item = newItem;
		setNext(nextNode);
	};

	ItemNode(Item newItem) {
		this->item = newItem;
		setNext(NULL);
	};

	Item* getItem() {
		return &this->item;
	};

	void setCustomer(Item newItem) {
		this->item = newItem;
	};
};

