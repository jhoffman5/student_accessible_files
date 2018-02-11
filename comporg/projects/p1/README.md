**All repos must be private**

The purpose of this project is to get used to creating projects in assembly language on Linux 
and run then against your tests and my *grading* scripts.

There is *no* programming needed in this project. In short, it is a gimmie.

# Sample output

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
