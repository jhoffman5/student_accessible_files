**All repos must be private**

# Project 3 - Sorted singly linked list

You are going to write an ```AArch64``` ISA program that implements a sorted singly linked list that supports insertion and deletion. The two most important aspects of this project are:
1. A first taste of using C and C++ like structs in assembly language.
2. Perfect memory management discipline. Your program will be valground mercilessly.

You know how to do this, you've done it before if you have taken Data Structures (2560).

# All behavior and output must match spec exactly

This project will be graded by my scripts. My scripts are dumb. So, you must be smart.

# The node

```c++
struct Node
{
	struct Node * next;
	unsigned int payload;
};
```

Notice the payload is an ```unsigned int```. No negative numbers will ever make it into the linked list. See below.

*You are strongly encouraged to test any assumptions about how the above struct is layed out in memory. It would really suck to be dead in the water before you even get in the actual water.*

# The command line

Any positive number provided on the command line is an insertion. Any negative number provided on the command line is a deletion of the number's absolute value.

```
$ ./a.out 10 20 30 -20
List starting from head:
node next: 0x412050 payload: 10
node next: 0x0 payload: 30
```

# Valgrind

Valgrind must produce NO errors. Also, this listing shows another sample output:

```
valgrind ./a.out 10 20 30 40 -20
==21795== Memcheck, a memory error detector
==21795== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==21795== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==21795== Command: ./a.out 10 20 30 40 -20
==21795== 
List starting from head:
node next: 0x49a60e0 payload: 10
node next: 0x49a6130 payload: 30
node next: 0x0 payload: 40
==21795== 
==21795== HEAP SUMMARY:
==21795==     in use at exit: 0 bytes in 0 blocks
==21795==   total heap usage: 5 allocs, 5 frees, 1,088 bytes allocated
==21795== 
==21795== All heap blocks were freed -- no leaks are possible
==21795== 
==21795== For counts of detected and suppressed errors, rerun with: -v
==21795== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

