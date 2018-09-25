# Project - DnD Character Generator

## Goal

You’ll write a very simple Dungeons and Dragons character generator. Nothing too fancy.

In this project you will use a number of new or recently introduced techniques and technologies. These include:
* C++ strings
* C++ arrays
* Random number generation

## Review

C arrays are introduced in section 5.1 of the etextbook. Imagine an integer. It holds just one value. This might be the number of strikes a batter is facing. Now imagine a box score for the home team - it typically contains 9 integers in a row.

![int vs c array](./int_vs_c_array.png)

Remember that an array of *n* elements has indicies ranging from *0* to *n - 1*. Individual members of an array are accessed like so (and this is the same for C and C++ arrays - vectors too but we haven't talked about those yet).

```c++
// print first and fourth inning score
cout << inning[0] << " " << inning[3];
```
**Computer scientists index (number) from zero!**

A C array is defined like so:
```c
int innings[9];
```
A C++ array is defined like so (assuming you included the ```<array>``` include file and used a ```namespace std```):
```c++
array<int, 9> innings;
```
A C++ array has a number of advantages including self-knowledge. Like this feature (which you will likely use in this assignment):
```c++
cout << "Length of the array is: " << innings.size() << endl;
```

You can initialize an array with values like so:
```c++
array<string, 3> flavors = { "chocolate", "vanilla", "tutti-fruity" };
```

**Warning: There are dragons before and after an array. Bad things happen when you poke the dragons. Bob poked a dragon. Bob got burned. Don't be like Bob.**

You can get a random number by calling ```rand()```. This function returns an integer between ```0``` and ```RAND_MAX```. The value of ```RAND_MAX``` is guaranteed to be at least 32767 but can be far larger.

If you do not seed the *RNG* you will get the same sequence of "random numbers". Seeding the RNG is done with ```srand(unsigned int seed)```. If ```seed``` is the same value, you get the same sequence. To get a more random output from ```rand()``` you will typically call ```srand()``` with the time-of-day like so:
```c++
srand((unsigned int)time(0));
```
This assumes ```<ctime>``` has been included. 

*Pro Tip: if you want repeatable random numbers, don't use the current time. Instead use a constant. This helps with debugging programs that use random numbers that fail in specific cases.*

## New / practice materials

Some new material includes:

* C arrays introduced in 5.1 and discussed in class
* C strings introduced in 5.14
* C++ arrays discussed in class
* C++ strings
* Random numbers - all of 2.18 in the etextbook
* Random numbers within a specific range - participation activity 2.18.4 and 2.18.5 and the text preceding these activities
* ```getline()``` covered in 2.14 of the etextbook.

Some practice concepts:

* splitting the big job of a program into smaller functions

## Requirements

You must follow these requirements exactly.

Your program must loop, asking for character names that may contain spaces, until the word "quit" is entered.

There are three attributes of a DnD character for which you will write specific functions. These are the signatures.
```c++
string ChooseRace();
string ChooseAlignment();
string ChooseBehavior();
```

Each chooses one value from an array of predefined values at random.

```c++
string ChooseRace();
```
can return one of:
* Human
* Orc
* Elf
* Dwarf
* Professor

```c++
string ChooseAlignment();
```
can return one of:
* Lawful
* Neutral
* Chaotic

```c++
string ChooseBehavior();
```
can return one of:
* Good
* Neutral
* Evil

You must write a function returning a random number within a give range. It will have the signature:
```c++
int RangeRand(int min, int max);
```
It will return a random integer whose minimimum value is specified as the first argument. Its maximum value is one less than the second argument. For example ```RangeRand(0, 10)``` returns a random integer from 0 to (including) 9. The mod operator ```%``` is important here.

You must write a function return a "stat". Stats can range between 6 and 18 inclusive. The highest (18) is special. If you roll an 18 (you chose 18 at random) the character gets a special massive boost which comes in the form of a number between 0 and 100 inclusive. Because of this, your function returns a string - not a number.

```c++
string PickStat();
```
See the sample output for an example of non-18 values and one special 18 value. You will choose stats for:
* Strength
* Dexterity
* Intelligence
* Charisma
* Wisdom

Health is different - it ranges from 6 to 30 inclusive. 

You can "add" two strings together and convert numbers to strings. Here is an example:

```c++
int agent_number = 99;
string s = "Hello there, Agent " + to_string(agent_number);
```

This results in the variable ```s``` containing ```Hello there, Agent 99```.

As a hint, here are the include files I used when writing my implementation:

```c++
#include <array>
#include <ctime>
#include <iostream>
#include <string>
```

These permit me to use C++ arrays and strings, seeding the random number generator and using cin and cout.

*Style: Sometimes you can have dozens of includes - fact of life. If they are in an order, they are easier to glance through.*

## Sample output

Notice two things about the sample output shown below.

First, blank answers are simply skipped. Your program must have this behavior.

Second, a multiple word entry is treated as all together as a single entry. This is not the case when you use the input operator ```>>```. Instead of something like:

```c++
cin >> character_name;
```

You will use ```getline()```. This material is covered in chapter 2.14 in your etextbook.

```
Enter character's name - use "quit" to exit: 
Enter character's name - use "quit" to exit: 
Enter character's name - use "quit" to exit: Hector the Horrible
Hector the Horrible (Elf) is Neutral alignment and Neutral behavior
Health: 15
Strength: 8
Dexterity: 13
Intelligence: 7
Charisma: 16
Wisdom: 6

Enter character's name - use "quit" to exit: Furry Curry Murray
Furry Curry Murray (Orc) is Lawful alignment and Evil behavior
Health: 17
Strength: 17
Dexterity: 9
Intelligence: 9
Charisma: 8
Wisdom: 18 / 74

Enter character's name - use "quit" to exit: quit
Hit enter to exit: 
```

## Partner rules

All work to be done individually.

## What to turn in and how

Turn in your single C++ source code via schoology.

## Grading

Grading is out of 100 points.

You will receive zero points if:

* You do not hand in a project.
* You hand in a file which is not cpp source code.
* Your code does not compile to completion.
* Your code is substantially incomplete.

You will receive ten points off if compiling your code produces *any* warnings.

You will receive ten points off if your name is not at the top of the program.

You will receive five points off for every required function that is missing, incomplete, or not according to specification. These are are:
```c++
string ChooseRace();
string ChooseAlignment();
string ChooseBehavior();
int RangeRand(int min, int max);
string PickStat();
```

Of course, more opportunities for reduced score exist.

## Postscript

Here is Hector being Horrible:
![hector](./hector.jpg)

Here is Murray being Furry after eating Curry:
![Murray](./murray.jpg)

