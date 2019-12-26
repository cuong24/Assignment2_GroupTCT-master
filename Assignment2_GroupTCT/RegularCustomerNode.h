class RegularCustomerNode : public Node {
private:
	RegularCustomer customer;
public:
	RegularCustomerNode(RegularCustomer newCustomer, Node *nextNode) {
		this->customer = newCustomer;
		setNext(nextNode);
	};

	RegularCustomerNode(RegularCustomer newCustomer) {
		this->customer = newCustomer;
		setNext(NULL);
	};

	RegularCustomer* getCustomer() {
		return &this->customer;
	};

	void setCustomer(RegularCustomer newCustomer) {
		this->customer = newCustomer;
	};
};