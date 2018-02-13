**All repos must be private**

The purpose of this project is to get used to creating projects in assembly language on Linux 
and run then against your tests and my *grading* scripts.

There is *no* programming needed in this project. In short, it is a gimmie.

# What you are to do

Even though there is no coding in this project, you do have things to do:
* Comb over every word in main.s and every instruction.
* Thoroughly absorb and understand what you find.
* Practice building an assembly language program.
* Practice using GDB.
* Practice using valgrind.
* Practice running my test scripts.

# Building the program

Without debugging support:

```gcc main.s```

With debugging support:

```gcc -g main.s```

Both produce ```a.out```.

# Running the program

When in the diretory where the program is:

```./a.out```

# Running the tests

This has my user name. Yours will be used for you.


```
/home/2510/2510.sh -p p1
Results will be written to /tmp/pkivolowitz_2510.txt
Overwrite output (Y|N) [N]? 
Y
Attempting: /home/2510/tests/p1/test_1.sh
Attempting: /home/2510/tests/p1/test_2.sh
Attempting: /home/2510/tests/p1/test_3.sh
Attempting: /home/2510/tests/p1/test_4.sh
```

# Seeing the results of the test

Replace my user name with your user name:

```
cat /tmp/pkivolowitz_2510.txt 
Tue Feb 13 07:07:32 CST 2018
Working on p1

Entering /home/pkivolowitz/comporg/projects/p1
Build SUCCEEDED
-rwxrwxr-x 1 pkivolowitz pkivolowitz 10208 Feb 13 07:07 a.out

Test 01 - presence of puts call
	bl	puts			// Call puts. puts() is coming from the C runtime library which is 
SUCCEEDED

Test 02 - deprecated
SUCCEEDED

Test 03 - enough comments
21 Comments
SUCCEEDED

Test 04 - Testing for correct output as per /home/2510/tests/p1/correct_output_01.txt
Expected result - must match letter for letter:
Hello, world! (From ARMV8 - 64 bit - assembly language)
Your output:
Hello, world! (From ARMV8 - 64 bit - assembly language)
SUCCEEDED
Leaving /home/pkivolowitz


```

# Sample output of the program

```
~/comporg/projects/p1$ ./a.out
Hello, world! (From ARMV8 - 64 bit - assembly language)
~/comporg/projects/p1$ 
```
# Practice valgrind

```
~/comporg/projects/p1$ valgrind ./a.out
==21845== Memcheck, a memory error detector
==21845== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==21845== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==21845== Command: ./a.out
==21845== 
Hello, world! (From ARMV8 - 64 bit - assembly language)
==21845== 
==21845== HEAP SUMMARY:
==21845==     in use at exit: 0 bytes in 0 blocks
==21845==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==21845== 
==21845== All heap blocks were freed -- no leaks are possible
==21845== 
==21845== For counts of detected and suppressed errors, rerun with: -v
==21845== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
~/comporg/projects/p1$ 
```
