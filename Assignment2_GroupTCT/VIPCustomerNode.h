class VIPCustomerNode : public Node {
private:
	VIPCustomer customer;
public:
	VIPCustomerNode(VIPCustomer newCustomer, Node *nextNode) {
		this->customer = newCustomer;
		setNext(nextNode);
	};

	VIPCustomerNode(VIPCustomer newCustomer) {
		this->customer = newCustomer;
		setNext(NULL);
	};

	VIPCustomer* getCustomer() {
		return &this->customer;
	};

	void setCustomer(VIPCustomer newCustomer) {
		this->customer = newCustomer;
	};
};