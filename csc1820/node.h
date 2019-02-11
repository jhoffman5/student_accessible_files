#pragma once

struct Node {
	Node();
	~Node();
	void SetValue(int v);
	void Insert(int v);
	void InfixEnumeration(Node *);
	struct Node * left , * right;
	int value;
	int count;
};