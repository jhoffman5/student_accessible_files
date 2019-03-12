# Tail - summative project in assembly language

The Unix ```tail``` program prints the last *n* lines of a file. You will write a subset of this program.

Valgrind must report NO errors in memory management.

# Fixed algorithm and data structures

Because I am testing specific skills, you **cannot** choose your data structure or algorithm.

You must use the equivalent of:

```
#define TAILLEN 10
char * tailbuffer[TAILLEN];
```

Since you will be asked to operate on files longer than ```TAILLEN``` lines, you must wrap around as many times as needed. Every thing you allocate must be freed. Everything. *EVERYTHING*.

**My scripts will change TAILLEN. That is why tailbuffer has to be allocated dynamically. Your code must handle this.**

If my code cannot find the equivalent of the ```#define``` as follows:

```
	.EQU	TAILLEN, 10
```

you earn a BIG discount on your grade. The ```.EQU``` is how you must do the ```#define```.

Looking at:

```
char * tailbuffer[TAILLEN];
```

Indicates that you must build a circular buffer of char pointers. You are required to allocate and free buffers for each line of text that you parse. 

You may assume that no line of input will be larger than 4K bytes. You may not simply allocate ```TAILLEN``` 4K buffers. This would defeat one of the main purposes of this assignment and would be dealt with harshly. Instead, you will dynamically allocate a "right sized" buffer for every line of text read with appropriate freeing of previously allocated lines which rotate off the circular buffer.

**REPEAT: My tests will modify TAILLEN so the above line must be perfectly typed in your source code. There is a single tab in front and a single tab between .EQU and TAILLEN. Use uppercase only, on this line, even though uppercase or lowercase would otherwise be permissible.**

# You must comment

Commenting will be graded this time. You must comment functions like so:

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
    as many as needed - this is *SO* here to help you
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
badalloc:	.asciz	"Allocating a tail line failed."
```

```usage``` is printed if you don't specify a file as your command line argument.

```badopen``` is printed if the file specified doen't open. It is used with ```perror()```.

```noline``` is printed if a long character array used to read text cannot be allocated.

```badtail``` is printed if a TAILLEN long array of pointers to char cannot be allocated.

# Additional requirements

## Runtime library and system call use

There exists a C version of ```getline()```. You may **not** use it. You must read and parse lines yourself. 

There exists a C library call ```getc()```. You may **not** use it. You must read using ```read()```.

File handling calls you are permitted to use:

- open
- close
- read

That's it. 

Other C library or system calls you are likely to use:

- malloc
- free
- memset
- strlen
- puts
- printf

## Use of perror

If a file cannot be opened, you must use ```perror()``` to print out why.

Notice that my error string labeled ```badopen``` has no trailing punctuation like all the other error messages. This is because it must be used as the prefix to the message printed by ```perror```. ```perror``` will supply a ```:``` between the prefix and the error message it prints.

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

# Partner rules

Partnerships are not allowed on this project. All work must be solo.



