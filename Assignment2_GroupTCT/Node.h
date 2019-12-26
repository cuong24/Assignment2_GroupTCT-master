class Node {
protected:
	Node* next = NULL;
public:
	Node() {};
	~Node() {};
	Node* getNext() {
		return this->next;
	};
	void setNext(Node *nextNode) {
		this->next = nextNode;
	};
};




