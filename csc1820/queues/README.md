# Queue

In this project you will create a simplified simulation of a single queue / multi server system. You've been in a million of these. Any time you join people on a single line waiting for the next available "agent" or "open window", you're in one of these.

Single queue / multi server is the most efficient way of satisfying many customers with many servers. 

A queue is a first in / first out data structure. New arrivals enter at the back and the oldest member is at the front.

Here are some references for you:

* [cppreference](http://en.cppreference.com/w/cpp/container/queue)
* [cplusplus](http://www.cplusplus.com/reference/queue/queue/)
* [zybooks](https://learn.zybooks.com/zybook/CARTHAGECSC1120KivolowitzSpring2018/chapter/14/section/6)

# The command line

You don't have to interact with this program. Use two command line arguments to specify the input data file name and the number of servers.

Here are some data files:

* [test 1](./test_1.txt)
* [test 2](./test_2.txt)
* [test 3](./test_3.txt)
* [test 4](./test_4.txt)

These data files contain integers, one per line. Each integer represents the number of minutes each customer will need from some server. As you read the file, start counting the lines from 1 so that the first line is customer 1 (not the usual CS counting from 0). You'll need to remember each customer's number for reporting purposes.

This project is "simplified" in that all your customers are thought to arrive at once.

The second command line argument is an integer which sets the number of servers. If this has value 1, then you have a single queue / single server system - the worst for customer happiness.

# Sample output

```test_2.txt``` contains 5 lines with a value of 1 on each line. Here is with 1 server:

```
5 work units read.
1 workers defined.
Worker:    1 finished customer    1 at minute: 1
Worker:    1 finished customer    2 at minute: 2
Worker:    1 finished customer    3 at minute: 3
Worker:    1 finished customer    4 at minute: 4
Worker:    1 finished customer    5 at minute: 5
```

Each customer waited in line and was serviced one at a time.

Here is the same file but with 5 servers.

```
5 work units read.
5 workers defined.
Worker:    1 finished customer    1 at minute: 1
Worker:    2 finished customer    2 at minute: 1
Worker:    3 finished customer    3 at minute: 1
Worker:    4 finished customer    4 at minute: 1
Worker:    5 finished customer    5 at minute: 1
```

With a server available for every customer, everyone finished in exactly the minimum time.

With two servers:

```
5 work units read.
2 workers defined.
Worker:    1 finished customer    1 at minute: 1
Worker:    2 finished customer    2 at minute: 1
Worker:    1 finished customer    3 at minute: 2
Worker:    2 finished customer    4 at minute: 2
Worker:    1 finished customer    5 at minute: 3
```

Here is the output of ```test_4.txt``` with 20 customers and 5 workers:

```
20 work units read.
5 workers defined.
Worker:    4 finished customer    4 at minute: 1
Worker:    1 finished customer    1 at minute: 2
Worker:    4 finished customer    6 at minute: 2
Worker:    5 finished customer    5 at minute: 2
Worker:    2 finished customer    2 at minute: 3
Worker:    3 finished customer    3 at minute: 4
Worker:    4 finished customer    8 at minute: 4
Worker:    2 finished customer   10 at minute: 5
Worker:    1 finished customer    7 at minute: 6
Worker:    1 finished customer   14 at minute: 7
Worker:    4 finished customer   12 at minute: 8
Worker:    5 finished customer    9 at minute: 8
Worker:    1 finished customer   15 at minute: 10
Worker:    2 finished customer   13 at minute: 10
Worker:    4 finished customer   16 at minute: 10
Worker:    4 finished customer   20 at minute: 11
Worker:    1 finished customer   18 at minute: 13
Worker:    2 finished customer   19 at minute: 13
Worker:    3 finished customer   11 at minute: 13
Worker:    5 finished customer   17 at minute: 17
```

# Discussion

Use a ```queue``` for loading up the customers. I suggest making a queue of a custom type that holds the customer's ID number (line number) and how much time they need from a worker. Add to the back of the queue. 

When you've read the whole file (adding to the back of the queue), close it and move on to distributing customers to your initially idle workers. Each time a customer is handed off to a worker, pop it from the front of the queue. It is possible you have more workers than customers. In this case, some workers will remain idle even from the start.

How can you manage a worker? Imagine the process of assigning a customer to a worker: You know what time it is right now. The customer can tell you how many minutes of the worker's time the customer needs. The worker, therefore can record the time at which they will be ready for the next customer.

Now you're ready to loop over time and workers. For each worker, are they ready for a new customer?

At the end of processing each tick of the clock you need to decide if you should loop around again. After all, customers keep moving off the queue and assigned to a worker. Workers clear customers by working on them a certain number of minutes and then get assigned a new customer. The simulations comes to an end when the queue is empty and all workers are idle.

