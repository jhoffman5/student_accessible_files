#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
	left = right = nullptr;
	value = 0;
	count = 1;
}

Node::~Node() {
	cout << "Destructor of node with value: " << value << " count: " << count << endl;
	if (left != nullptr)
		delete left;
	if (right != nullptr)
		delete right;
}

void Node::SetValue(int v) {
	value = v;
}

void Node::Insert(int v) {
	if (v == value)
		count++;
	else if (v < value) {
		// Notice left and right has same code... 
		// It would be nice to combine them, wouldn't it?
		// But how?

		// left subtree
		if (left != nullptr) {
			left->Insert(v);
		} else {
			left = new Node();
			left->SetValue(v);
		}
	} else {
		// right subtree
		if (right != nullptr) {
			right->Insert(v);
		} else {
			right = new Node();
			right->SetValue(v);
		}
	}
}

void Node::InfixEnumeration(Node *) {
	// Write this so that all the nodes are printed in ascending order.
}
