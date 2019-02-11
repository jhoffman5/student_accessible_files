#include <iostream>
#include <string>
#include <exception>
#include "node.h"

using namespace std;


int main(int argc, char * argv[]) {
	int retval = 0;
	string line;

	Node * root = nullptr;
	while (getline(cin, line)) {
		if (line.size() > 0) {
			try {
				int v = stoi(line, nullptr);
				if (root == nullptr) {
					root = new Node();
					root->SetValue(v);
				} else {
					root->Insert(v);
				}
			} catch (invalid_argument) {
				cout << "Invalid integer" << endl;
				continue;
			} catch (out_of_range) {
				cout << "Out of range" << endl;
				continue;
			}
		}
	}
	if (root != nullptr)
		delete root;
	return retval;
}
