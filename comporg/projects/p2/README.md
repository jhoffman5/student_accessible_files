**All repos must be private**

# P2 - Enumerating ARGV

In this project you must write a program that enumerates argv.

Given: ```./a.out one two three```

You must output:

```
./a.out
one
two
three
```

## Requirements
1. Your source code file (exactly one) must be named main.s
2. Your output must match automatic testing output letter for letter.
3. Your code must be tight and efficient.
To wit: In my solution I did setup in 2 assembly statements, the actual loop
enumerating argv in 4 assembly statements and cleanup in 3 more assembly language
statements. That's right, you can author this project in 9 lines of actual code
(plus assembly language boiler plate).

   **There will be a deduction if your assembly language statement count (actual 
instructions - no counting comments or directives) are more than 12.**

4. You must use ```puts``` for output.

# Valgrind

Valgrind must NOT find errors:

```
~/comporg/projects/p2$ valgrind ./a.out foo bar "foo bar"
==21814== Memcheck, a memory error detector
==21814== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==21814== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==21814== Command: ./a.out foo bar foo\ bar
==21814== 
./a.out
foo
bar
foo bar
==21814== 
==21814== HEAP SUMMARY:
==21814==     in use at exit: 0 bytes in 0 blocks
==21814==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==21814== 
==21814== All heap blocks were freed -- no leaks are possible
==21814== 
==21814== For counts of detected and suppressed errors, rerun with: -v
==21814== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
~/comporg/projects/p2$ 
```


