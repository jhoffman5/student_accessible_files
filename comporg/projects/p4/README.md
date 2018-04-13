**All repos must be private**

# P4 - tail - print the last TAILLEN lines of any text file

This project tests your ability to keep track of memory, both allocating and deallocating.

Also tested is your ability to solve problems that would be relatively simple C programs.

Valgrind must report NO errors in memory management.

# Tips

If you use C++, use only things you can *easily* get rid of in assembly language. For example:

```
cout << "This is a test." << endl;
```

is easily replaced with:

```
    ldr     x0, =s
    bl      puts
```

and 

```
    .data
s:  .asciz  "This is a test."
```

But, using more advanced features of C++ will be very very difficult to translate into assembler.

Remember that some registers cannot be counted upon to be the same when a call to anything you
did not write returns.

# The algorithm and data structures are not yours to decide

Because I am testing specific skills, you cannot choose your data structure or algorithm.

You must use the equivalent of:

```
#define TAILLEN 10
char * tailbuffer[TAILLEN];
```

Since you will be asked to operate on files longer than ```TAILLEN``` lines, you must wrap around as many times as needed.
Every thing you allocate must be freed. Everything. *EVERYTHING*.

**My scripts will change TAILLEN. That is why tailbuffer has to be allocated dynamically. Your code must handle this.**

If my code cannot find the equivalent of the ```#define```:

```
	.EQU	TAILLEN, 10
```

You earn a BIG discount on your grade. The ```.EQU``` is how you do the ```#define```, by the way.

**REPEAT: My tests will modify TAILLEN so the above line must be perfectly typed in your source code.**

There is a single tab in front and a single tab between .EQU and TAILLEN.

# You must comment

Commenting will be graded. You must comment functions like so:

```
/*
<C version of the function's signature>

<High level description of the function>

Parameters:
    <register>    <description>
    as many as needed
    
Returns:
    <register>    <description>
    typically just one
    
Registers preserved:
    <register>    <description>
    as many as needed - this is SO here to help you
*/
```

At a minimum, comments inside your code should appear *between* logical blocks. 

```
    // Perform validation on arguments
    
    <several lines of code>
    
    // If we get here, open file.
    
    <several lines of code>
```

In addition, you *can* comment to the side of code. But a lot of these can get messy.

# Required error messages

The following will be checked. They must appear letter for letter.

```
usage:		.asciz	"File name must be given."
badopen:	.asciz	"Open file failed"
noline:		.asciz	"Allocating line buffer failed."
badtail:	.asciz	"Allocating tail pointer buffer failed."
dbgprnt:	.asciz	"Bytes read: %d String: %s\n"
badalloc:	.asciz	"Allocating a tail line failed."
pstring:	.asciz	"%s"
```

```usage``` is printed if you don't specify a file as your command line argument.

```badopen``` is printed if the file specified doen't open.

```noline``` is printed if a long character array used to read text cannot be allocated.

```badtail``` is printed if a TAILLEN long array of pointers to char cannot be allocated.

# Testing

Your program must match letter for letter the output expected by my test programs.

For example - this file is only three lines long:

```
./a.out test1.txt 
1. This is a test. There are three lines total.
2. This is another test.
3. And last one.
```

This file is very long:

```
./a.out main.s
usage:		.asciz	"File name must be given."
badopen:	.asciz	"Open file failed"
noline:		.asciz	"Allocating line buffer failed."
badtail:	.asciz	"Allocating tail pointer buffer failed."
dbgprnt:	.asciz	"Bytes read: %d String: %s\n"
badalloc:	.asciz	"Allocating a tail line failed."
pstring:	.asciz	"%s"

		.end
```

# Valgrind

Amongst all its output, Valgrind must produce this (ignore the number at the beginning of the line):

```
==21779== All heap blocks were freed -- no leaks are possible
```

