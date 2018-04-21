# Synchronization

In this project I give you the source code I used to develop the singly linked list project. I developed it first
in C then converted it to ASM. Here, I have modified it to C++ and added C++ 11 threading to stress the data structure
causing it to either work or crash in one of a number of ways.

The program, as you can see by reading the source code, takes two optional command line arguments. -h will print help.
-v enables some print out.

# The Worker

Here is (some version - may be out of date) the worker where the business happens:

```c++

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
```

As you can see, each worker will choose to terminate when the global variable global_shutdown is turned to true. The main
thread will sleep for a few seconds then set this variable to true. If the threads are still alive, they'll terminate
normally. If they aren't alive and well, well, that's the problem you are here to solve.

# The solution

You can solve this problem in either a gross manner (a BFL) or a more fine grained manner. You might try the BFL first 
just to get accustomed to using mutexes. But that will not earn you full credit. Note that it might be possible to solve
in too fine grained a manner. You should talk about it.

# Work rules

Same as previous project - partner based.

# What to turn in

Source code by one partner turned in via elearning. Make sure the source code includes the name of one or two people
the partners). The other person must upload a text file containing the name of the person in whose name the source 
code will be found.
