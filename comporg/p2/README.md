# File stat

This project teaches how to:

- access members of a struct.
- calculate offsets within a struct
- a very modest amount of bit manipulation

# Linux command ```stat```

Here is the output of the Linux command ```stat```.

```
$ stat main.s
  File: main.s
  Size: 2546      	Blocks: 8          IO Block: 4096   regular file
Device: fe02h/65026d	Inode: 132424      Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/    user)   Gid: ( 1000/    user)
Access: 2019-02-24 13:03:46.727764970 -0600
Modify: 2019-02-24 13:03:39.000000000 -0600
Change: 2019-02-24 13:03:40.723544815 -0600
 Birth: -
```

This shows:

| Item | Meaning |
| ---- | ------- |
| File | The file name |
| Size | The file's size in bytes |
| Blocks | The number of 512 byte blocks occupied by the file |
| Inode | This is the only unique identifier in a Unix file system |
| Access | This is the file's protection bits |
| "regular file" | The file is a "regular file" not a directory or other type of special file |

# Output of your program

You are writing a subset of the ```stat``` program. You will print this (in exactly the same format as given):

```
$ ./a.out main.s
Name:   main.s
Inode:  132424
Mode:   644, Regular File
Bytes:  2546
Blocks: 8
```

# The ```stat``` system call

```c
struct stat {
	unsigned long	st_dev;		// Device. 
	unsigned long	st_ino;		// File serial number. 
	unsigned int	st_mode;	// File mode.  
	unsigned int	st_nlink;	// Link count.  
	unsigned int	st_uid;		// User ID of the file's owner.  
	unsigned int	st_gid;		// Group ID of the file's group. 
	unsigned long	st_rdev;	// Device number, if device.  
	unsigned long	__pad1;
	long		st_size;	// Size of file, in bytes.  
	int		st_blksize;	// Optimal block size for I/O.  
	int		__pad2;
	long		st_blocks;	// Number 512-byte blocks allocated. 
	long		st_atime;	// Time of last access.  
	unsigned long	st_atime_nsec;
	long		st_mtime;	// Time of last modification.  
	unsigned long	st_mtime_nsec;
	long		st_ctime;	// Time of last status change.  
	unsigned long	st_ctime_nsec;
	unsigned int	__unused4;
	unsigned int	__unused5;
};
```

You need to allocate either statically or dynamically a buffer to hold one of these. To do so, you must know the struct's size. 

Dynamic allocation can, of course, be done with ```malloc```. If you use this, you must check its return value and perform a ```free.```

Alternatively you can statically declare space in the ```.data``` segment. For example:

```
	.data
buffer:	.space 16
```

This allocates 16 bytes with the label ```buffer```.

# Fetching from memory

In class you learned that you can fetch memory based dereferenced from an address:

```
	ldr	x1, [x0]
```

This fetches 8 bytes from the memory whose address is in x0.

You also learned:

```
	ldr	w1, [x0]
```

fetches 4 bytes.

```
	ldrh	w1, [x0]
```

fetches 2 bytes and

```
	ldrb	w1, [x0]
```

fetches 1 byte.

# Layout of struct / class members in memory

Consider this ```struct```:

```c
struct Foo {
	long	a;
	int	b;
	short	c;
	char	d;
};
```

The members of ```Foo``` has the following offsets:

```
struct Foo {
0	long	a;
8	int	b;
12	short	c;
14	char	d;
};
```

You can see that the number of bytes consumed by the members of ```Foo``` totals 15 bytes. Yet, ```sizeof(Foo)``` returns 16, not 15. All data types have a natural alignment requirement.

Consider:

```
struct Foo {
	long	a;
	int	b;
	short	c;
	char	d;
	long	e;
};
```

Member ```e``` has offset 16, not 15. The overall size is 24 bytes. Notice the 8 byte long begins on a multiple of 16.

Consider:

```
struct Foo {
	long	a;
	int	b;
	short	c;
	long	d;
	char	e;
};
```

This changes things considerably even though I have switched the order of only two members.

The offsets are like this now:

```
struct Foo {
0	long	a;
8	int	b;
12	short	c;
16	long	d;
24	char	e;
};
```

And the size is 32 yet the members account for 25 bytes. Can you explain this? Do you see the pattern?

# Fetching from an offset

How does one access these members given that the address of an instance of ```Foo``` (assumes the final version of the struct above) is located in x19?

```
	ldr	x0, [x19]	// a
	ldr	w0, [x19, 8]	// b
	ldrh	w0, [x19, 12]	// c
	ldr	x0, [x19, 16]	// d
	ldrb	w0, [x19, 24]	// e
```

# Double checking your assumptions of layout

You can double check any assumptions you make about layout like this:

```c++
	cout << "a " << (char*) &f.a - (char*) &f << endl;
	cout << "b " << (char*) &f.b - (char*) &f << endl;
	cout << "c " << (char*) &f.c - (char*) &f << endl;
	cout << "d " << (char*) &f.d - (char*) &f << endl;
	cout << "e " << (char*) &f.e - (char*) &f << endl;
```

# The mode of the file

```st_mode``` is 32 bits. You are required to print out (in octal) only the low 9 bits.

You are also required to print that a file is a directory, a regular file or another type of file. The bit locations are given below in the form of C / C++

```c++
#define __S_IFDIR       0040000 Directory.
#define __S_IFREG       0100000 Regular file.
```

Notice these values begin with a leading 0. This means these are octal.

Here are examples of each type of file:

```
user@comporg:~/src/fstat$ ./a.out a.out
Name:   a.out
Inode:  132425
Mode:   755, Regular File
Bytes:  10984
Blocks: 24

user@comporg:~/src/fstat$ ./a.out .
Name:   .
Inode:  132423
Mode:   755, Directory
Bytes:  4096
Blocks: 8

user@comporg:~/src/fstat$ ./a.out /dev/null
Name:   /dev/null
Inode:  1044
Mode:   666, Other type of file
Bytes:  0
Blocks: 0
```

# Partner rules

You may work with a partner.







