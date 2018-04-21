/*	Singly linked list - not thread safe.
	Perry Kivolowitz
	Carthage College

	You can fix this in a gross manner or you can fix this in a better manner. 
	Your job is to fix this in a non-gross manner.
*/

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <cassert>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>

#define nullptr NULL

using namespace std;

struct Node
{
	struct Node * next;
	unsigned int payload;
};

struct Node * head = nullptr;
bool global_shutdown = false;

void BusyWait(suseconds_t t) {
	timeval now;
	timeval increment;
	timeval end;

	increment.tv_sec = 0;
	increment.tv_usec = t;

	gettimeofday(&now, nullptr);
	timeradd(&now, &increment, &end);
	while (true) {
		gettimeofday(&now, nullptr);
		if (timercmp(&now, &end, >))
			break;
	}
}

void Delete(unsigned int payload)
{
	struct Node * n = head;
	struct Node * p = NULL;

	while (n != NULL) {
		if (n->payload == payload) {
			if (p == NULL) {
				head = n->next;
			}
			else {
				p->next = n->next;
			}
			free(n);
			break;
		}
		p = n;
		n = n->next;
	}
}

struct Node * Insert(unsigned int p) 
{
	struct Node * n = (struct Node *) malloc(sizeof(struct Node));
	n->payload = p;
	n->next = nullptr; 
	if (head == nullptr) {
		head = n;
	}
	else if (p <= head->payload) {
		n->next = head;
		head = n;
	}
	else {
		struct Node * current = head;
		while (current->next != nullptr && current->next->payload < p) {
			current = current->next;
		}
		n->next = current->next;
		current->next = n;
	}
	return n;
}

void Print(struct Node * p)
{
	while (p != nullptr) {
		printf("%d\n", p->payload);
		p = p->next;
	}
}

void Worker(bool verbose) {
	while (!global_shutdown) {
		int n = rand() % 500 - 250;
		if (n < 0) {
			if (verbose)
				cout << "D" << flush;
			Delete((unsigned int) -n);
		} else {
			if (verbose)
				cout << "I" << flush;
			Insert((unsigned int) n);
		}
		BusyWait(rand() % 100 + 100);
	}
}

int main(int argc, char * argv[])
{
	bool verbose = false;
	int c;

	srand((unsigned int) time(NULL));
	vector<thread> t(thread::hardware_concurrency());

	while ((c = getopt(argc, argv, "vh")) != -1) {
		switch (c) {
			case 'v':
				verbose = true;
				break;

			case 'h':
				cout << "usage: -h this text\n";
				cout << "       -v verbose mode\n";
				break;
		}
	}

	for (auto & i : t)
		i = thread(Worker, verbose);

	sleep(3);
	global_shutdown = true;

	int j = 0;
	for (auto & i : t) {
		i.join();
		cout << "Join: " << j++ << endl;
	}
	cout << "Joined.\n";

	return 0;
}

