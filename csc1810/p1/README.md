# Project - Basic operators in expressions

## Goal

Given two integers, two floats and two bools to which you assign fixed values, print the value of various expressions using them.

This project provides:
•	Experience creating a program from scratch in our VM.
•	Practice using cout to print literal strings and expressions.
•	Insight into the nature of expressions.

## Discussion

Starting from here:
```c++
#include <iostream>

using namespace std;

int main()
{
	// Your code goes here

  cout << "Hit enter to exit: ";
  cin.get();
  cin.get();
  return 0;
}
```

Define two ```int```, two ```float``` and two ```bool``` variables giving them names of your choosing. In this case, choosing overly short and non-descriptive variable names like “a” and “b” is acceptable. 

*Style: In general, such variable names are not good style because they aren’t very descriptive.*

In the following you will have a sequence of output for the integers, then for the floating point numbers and then for the boolean values.

Using the computer to perform all calculations, write a program to output the following as close as you can with the known exception that your variable names and values may differ:

```
a and b are integers
a is:      19
b is:      37

a + b:     56
a - b:     -18
a * b:     703
a / b:     0
a % b:     19

-a is:     -19
-b is:     -37

a == b	is: 0
a < b 	is: 1
a <= b	is: 1
a > b 	is: 0
a >= b	is: 0
a != b	is: 1

f and g are floats
f is:      19
g is:      37

f + g:     56
f - g:     -18
f * g:     703
f / g:     0.513514

-f is:     -19
-g is:     -37

f == g is: 0
f <  g is: 1
f <= g is: 1
f >  g is: 0
f >= g is: 0
f != g is: 1

x and y are bools
x is:      0
y is:      1

x + y:     1
x - y:     -1
x * y:     0
x / y:     0
x % y:     0

-x is:     0
!x is:     1
-y is:     -1
!y is:     0

x == y is: 0
x <  y is: 1
x <= y is: 1
x >  y is: 0
x >= y is: 0
x != y is: 1
Hit enter to exit: 
```

Again:
* You are free to change variable names.
* You are free to provide different values.

# Sections from the reading that may help

Consult zybooks sections:
* 2.4 General arithmetic expressions
* 2.5 Integer arithmetic expressions
* 2.6 Floating point arithmetic expressions
* 2.10 Integer division and modulo

# Gotcha's

## Printing along with the logical operators
When you print out the value of the six basic logical operators, you will likely encounter a little complication.

Hint: “<<” has higher precedence than the logical operators just like * has a higher precedence than +. 

Precedence is the notion of applying an order to operations. You have known about precendece since grade school when you learned that multiplication has a higher precedence than addition. Thus: ```8 * 2 + 4``` is always 20 and not 48. In grade school you learned to use parenthesis to influence / change precedence. The same is true in C and C++.

## Printing the value of bools

The value of a logical operation is 0 if false and 1 if true. So, if you print out the result of ```a > b``` you will not see ```true``` or ```false```. Rather you will see 0 or 1. See the section on Extra Credit.

## There is no mod operator for float or bool

Notice there is no ```%``` operator for floats or bools.

## There is a big difference between ```!``` and ```-``` for bools.

Notice there are two extra statements for bools leading off with ```!```.

## Initializing a bool

Is done like so:
```c++
bool foo = false;
```

The words ```true``` and ```false``` must be all lowercase. These *reserved words* do not exist in C, only in C++.

## Remember the blank lines

For example:
```
b is:      37

a + b:     56
```
Remember the blank line.

## You are not allowed to define any additional variables

This encourages you to understand that expressions are evaluated whether or not there is an assignment.

## Major points off if you stand in for the computer

*You are not to do the calculating. Rather the computer must do it.* For example, if your ```a``` and ```b``` are 4 and 6 respectively, you must do this:
```c++
cout << "a + b: " << a + b << endl;
```
and not this:
```c++
cout << "a + b: 10" << endl;
```

# Partner rules

*To be defined by the instructor.*

# What to turn in and how

Use schoology to turn in only your one cpp source code file.

# Grading

Grading is out of 100 points.

You will receive zero points if:
* You do not hand in a project
* You hand in a file which is not cpp source code.
* Your code does not compile to completion.

You will receive ten points off if compiling your code produces *any* warnings. It is quite possible to generate warnings in writing this program.

You will receive ten points off if your name is not at the top of the program.

You will receive thirty points off if *you* do any of the calculations instead of the computer. This is discussed above.

You will receive twenty points off if your code produces *any* wrong results.

If you have run afoul of none-of-the-above, then you receive 100 percent.

# Extra credit

Five points (on the hundred scale) will be added if you take it upon yourself to discover how to print "true" and "false" where appropriate replacing 1 and 0. Zybooks sections 3.1 and 3.2 might help.

# Additional learning

## Integer types

There are several different names for integer types different in important ways.

| name | nominal size (bits) |
|:-:|---|
| char  |  8 |
| short  | 16 |
| int | 32 |
| long | 64 |
| long long | 64 |

A ```bit``` is a single binary value - either 0 or 1. A one bit integer (kind of like ```bool```) can hold 2<sup>1</sup> different values (i.e. 2).

A ```char``` is a small integer, having but 8 bits. It can represent 2<sup>8</sup> different values (256).

A 32 bit integer can represent 4,294,967,296 values.

A 64 bit integer can represent 18,446,744,073,709,551,616 different values. To put this in perspective let us cite to comparisons. 

1. 2<sup>64</sup> is about twice the estimated number of grains of sand on Earth.
2. Consider one pixel on your screen. If you lined up pixels starting from the center of the Sun, 2<sup>64</sup> of them would be about the orbit of Saturn.

We will study this more deeply as we progress in our studies.

## Float types

There are two kinds of floating point types in C++. ```float``` and ```double```. Both area capable of representing fractional values - this is what distinguishes floating point values from integers. ```float``` values sit in 32 bits. ```double``` values sit in 64 bits (double as much space).

If one were to divide the distance from Earth to the Sun (in very round numbers because of the orbit of the Earth is not a perfect circle), a ```float``` can account for every 10 kilometers. A ```double``` divides the same distance into the width of a human hair.

## The trouble with floats

Read this then put it away. Neither floats nor doubles are always exact. As you know, some numbers have no finite precision value such as pi or e. Certainly, floats nor doubles can do any better. Amazingly, some seemingly ordinary numbers are also *inexact*. More on this someday.
