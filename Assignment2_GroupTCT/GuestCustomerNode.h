class GuestCustomerNode : public Node {
private:
	GuestCustomer customer;
public:
	GuestCustomerNode(GuestCustomer newCustomer, Node *nextNode) {
		this->customer = newCustomer;
		setNext(nextNode);
	};

	GuestCustomerNode(GuestCustomer newCustomer) {
		this->customer = newCustomer;
		setNext(NULL);
	};

	GuestCustomer* getCustomer() {
		return &this->customer;
	};

	void setCustomer(GuestCustomer newCustomer) {
		this->customer = newCustomer;
	};
};