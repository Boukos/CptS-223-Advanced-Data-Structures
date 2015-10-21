#include <cstddef> // needed to use NULL

#ifndef REVERSIBLESTACK_H
#define REVERSIBLESTACK_H

class ReversibleStack {
private:
	struct Node {
		int data;
		Node* next;
	};

public:
	Node* top;

	ReversibleStack() {
		top = NULL;
	}

	~ReversibleStack(){
		Empty();
	}

	void Push(int newval) {
		Node *tmp = new Node;                   // create new node tmp

		tmp->data = newval;                     // set new node value to x
		tmp->next = top;                        // points to old top of the ReversibleStack
		top = tmp;                              // now the top
	}

	int Pop() {
		if (top == NULL) return NULL;           // if the list is empty, return NULL
		int topVal = top->data;

		Node* oldTop = top;
		top = top->next;
		delete oldTop;

		return topVal;
	}

	void Reverse() {
		ReversibleStack* newStack = new ReversibleStack();  // have to use new to allocate new memory, otherwise it gets deleted when the function ends
		while (!IsEmpty()) newStack->Push(Pop());
		Node* oldTop = top;
		top = newStack->top;  // our top is not pointing to the top of the new, reversed stack
		delete oldTop;        // delete the old top which is now pointing to an empty stack
	}

	void Empty() {
		while (!IsEmpty()) Pop();
	}

	int IsEmpty() {
		return (top == NULL);    // checks if ReversibleStack is empty
	}
};

#endif