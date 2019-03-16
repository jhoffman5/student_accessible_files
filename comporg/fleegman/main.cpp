#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <ctime>
#include <getopt.h>

/*	Dining Philosophers with two solutions.

	Presented for coding in class as Fleegman's Dilemma so that students don't
	simply look up the solution. Rather than using phtread (directly), this 
	example uses the c++11 standard wrappers.

	Perry Kivolowitz
	Computer Science
	Carthage College
	Kenosha, WI
*/

using namespace std;

const int NUM_THREADS = 5;
thread * threads[NUM_THREADS];
mutex  forks[NUM_THREADS];

void ProtectedCout(const string s)
{
	static mutex cout_lock;
	cout_lock.lock();
	cout << s << endl;
	cout_lock.unlock();
}

void WorkerDeadLock(unsigned int thread_id)
{
	while (true)
	{
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 4 + 1));
		forks[thread_id].lock();
		forks[(thread_id + 1) % NUM_THREADS].lock();
		ProtectedCout("Fleegman[" + to_string(thread_id) + "] is fleegling");
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 8 + 1));
		forks[(thread_id + 1) % NUM_THREADS].unlock();
		forks[thread_id].unlock();
	}
}

void WorkerCycleBreaker(unsigned int thread_id)
{
	while (true)
	{
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 4 + 1));
		if (thread_id == 0)
		{
			forks[(thread_id + 1) % NUM_THREADS].lock();
			forks[thread_id].lock();
		}
		else
		{
			forks[thread_id].lock();
			forks[(thread_id + 1) % NUM_THREADS].lock();
		}
		
		ProtectedCout("Fleegman[" + to_string(thread_id) + "] is fleegling");
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 8 + 1));
		forks[(thread_id + 1) % NUM_THREADS].unlock();
		forks[thread_id].unlock();
	}
}

void WorkerTryLock(unsigned int thread_id)
{
	while (true)
	{
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 4 + 1));
		try_lock(forks[thread_id], forks[(thread_id + 1) % NUM_THREADS]);
		ProtectedCout("Fleegman[" + to_string(thread_id) + "] is fleegling");
		std::this_thread::sleep_for(chrono::milliseconds(rand() % 8 + 1));
		forks[(thread_id + 1) % NUM_THREADS].unlock();
		forks[thread_id].unlock();
	}
}


int main(int argc, char * argv[])
{
	void (* worker)(unsigned int) = WorkerDeadLock;
	int c;

	while ((c = getopt(argc, argv, "dcth")) != -1) {
		switch (c)
		{
			case 'd':
				worker = WorkerDeadLock;
				break;

			case 'c':
				worker = WorkerCycleBreaker;
				break;

			case 't':
				worker = WorkerTryLock;
				break;

			case 'h':
			default:
				cerr << "-d for deadlocks (default)\n-c for cycle break solution\n-t for try_lock solution\n";
				exit(0);
		}
	}
	srand((unsigned int) time(nullptr));
	for (unsigned int i = 0; i < NUM_THREADS; i++)
		threads[i] = new thread(worker, i);

	for (unsigned int i = 0; i < NUM_THREADS; i++)
		threads[i]->join();

	return 0;
}