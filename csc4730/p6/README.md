# P6 - Named Pipe

## Objectives

You are going to write two programs.

1. A program to write to a shared memory buffer. The producer.

2. A program to read from a shared memory buffer. The consumer.

Together these will implement what is known as a named
pipe. In a previous project you used anonymous pipes. Both ends of the pipe needed to derive from the name parent so that they would have knowledge of the pipe. A named pipe is different.

A named pipe is an entity on the file system that all can see and open like a file. With a real named pipe, writing to it like a file produces content in the pipe. Reading from the named pipe like a file drains content from the pipe.

While an infinite amount of data can pass through the pipe, only a specific amount can be in the pipe at any given time. 

* When the pipe is full, the producer goes to sleep.

* When the pipe is empty, the consumer goes to sleep.

When the pipe changes state between full or empty the appropriate party must be awakened as it may have been put to sleep.

## Not a real named pipe

Real named pipes are built in the kernel. Ours will be made entirely in user land using a technique called "shared memory" (shmem) using "shared memory operations" (shmops). This functionality was added to AT&T Unix System V and later adopted by other Unix systems.

You know how this is implemented by the kernel - it adds a number of identical page table entries to more than one process. Presto-chango, bob's your uncle, shared memory.

## What you are given

### Monitor

I provide a watch dog program named "monitor". 

*Run this program first before you launch your own.*

The monitor is responsible for creating the shared memory region. Part of the shared memory region are data structures which both of your programs must use. If the monitor is not run first, your programs cannot work.

After initialization, the monitor will give you a clue as to the status of your named pipe. You can learn if the pipe is full, empty, or inbetween.

### My producer and my consumer

Out of kindness, I give you working executables for a producer and consumer.

This is a major benefit to you:

* You are free to develop one side then the other instead of both sides at once.

* Your producer and consumer will be graded against mine so having them means you will have a clue as to whether or not you will receive a failing grade (again).

### A makefile

Here is what I used:

```
CC		= g++
#CFLAGS		= -Wall
CFLAGS		= -Wall -O3
LFLAGS		= -lpthread -lrt
ALL			= producer consumer 


producer	:	producer.cpp shmem.h shmem.cpp
			$(CC) -o producer $(CFLAGS) producer.cpp shmem.cpp $(LFLAGS)


consumer	:	consumer.cpp shmem.h shmem.cpp
			$(CC) -o consumer $(CFLAGS) consumer.cpp shmem.cpp $(LFLAGS)

all		:	$(ALL)

clean		:	
			rm -f *.o $(ALL)
```

You can use this or not. You make ```shmem.h``` yourself - but it must include the stuff (Hint 3) below verbatim. 

### The shared memory layout

See Hint 3. *Any* deviation from this layout will result in a non-working project.

## What you are not given

After the performance project 5, I have decided to give you essentially no specification. You figure it out.

**Like in the real world**.

## Hint 1

Consult chapter 31 of OSTEP. specifically Figure 31.12. 

No, you won’t be able to use this code
directly. It serves only as a model. Plus, this code assumes the producer and consumer are in
the same process.

And, this doesn't manage a circular buffer. See Hint 8.

## Hint 2

You figure out shmem and shmops.

http://man7.org/linux/man-pages/man7/shm_overview.7.html

## Hint 3

Synchronization is done using atomic instructions which manipulate ordinary memory. 
Since you can access the same range of physical memory from several virtual address spaces, if each
program uses the same layout of semaphores and mutexes, then they’re all able to become
synchronized.

This is the shared memory layout. I am not even giving you this as an include file. You make it. You'll want a whole boat load of includes. You figure them out.

```c++
#define	BUFFER_SIZE		4096
#define	SHMEM_NAME		"/p5shmem"

struct SharedMemory
{
	time_t csol;
	time_t psol;
	sem_t block;
	sem_t emptyCount;
	sem_t fillCount;
	int p_index;
	int c_index;
	unsigned char buffer[BUFFER_SIZE];
};
```

## Hint 4

pthreads

## Hint 5

```sem_t```

This is required as any other technique will fail. As in your grade.

## Hint 6

The producer, until killed, writes whatever to the write side of the producer / consumer thing
you’re making. As a result of your successful code, the producer will go to sleep when the 4096
bytes of buffer are full.

It wakes up when there’s room in the buffer.

After every write, the producer writes the time into ```sol_producer```. sol means Sign Of Life.


The consumer, until killed, reads whatever from the read side of the producer / consumer thing
you’re making. As a result of your successful code, the consumer will go to sleep when the
buffer is empty. 

The consumer wakes up when there’s data back in the buffer.

After every read, the consumer writes the time into sol_consumer.

## Hint 7

Each time you wrote or read you update the sign-of-life fields. The Watch Dog can tell you that
your program is still operating. If the clocks stop, you’re deadlocked. 

## Hint 8

Circular buffer.

## Hint 9
Comment the HECK out of this code. 

## Hint 10

Try my three programs to figure out what you are supposed to transmit and receive.

## Hint 11

You are on your own. I am not answering any questions other than part of normal class content presentation.

## Hint 12

This is **not** punitive. This is career prep.

## Grading

We are going to grade this in class - just like P5.

## Working together

You may work in pairs.

## What to Hand In

All source code.

