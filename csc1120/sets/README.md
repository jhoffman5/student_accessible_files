**All repos must be private**

# New information:

## Project has been refactored away from zybooks

You will develop and hand-in this project the old-fashioned way, through elearning. Remember to upload only your source file.

## Use of argv and argc. 

Please configure your projects to use an optional command line argument. If given, the command line argument is the name of a file that contains an initial set of input for your testing. I will use these files as a shortcut rather than entering a bunch of test data manually. Manual input via the ```add``` command should still work.

## Configuring (setting) a command line argument

We did this in class:
* XCode: modify the "scheme."
* Visual Studio: modify the project settings.

## Sample files

Here are the small test files I used. You can add to these or make your own.

[an empty file](./empty.txt)

[a file with bad symbols](./bad_symbols.txt)

[a file with good symbols](./small_good_symbols.txt)

You can download these using the right click on the link method in your browser.

# The set container

## Online references:

* [cppreference](http://en.cppreference.com/w/cpp/container/set)
* [cplusplus](http://www.cplusplus.com/reference/set/set/)
* [zybook 14.5](https://learn.zybooks.com/zybook/CARTHAGECSC1120KivolowitzSpring2018/chapter/14/section/5)

## Mini tutorial

You have used one ```Standard Template Library``` container quite a lot: ```vector```.

Now, let's get to know another one: ```set```.

Like ```vector```, you need to include something.

```c++
#include <set>
```

Like ```vector```, you can customize what it holds.

```c++
set<string> flavors;
```

Like ```vector```, you can add to and subtract from a ```set``` as much as you like. 

```c++
flavors.insert("vanilla");
flavors.erase("chocolate");
```

Unlike ```vector``` which can use ```iterators```, ```set``` containers **must** be accessed via ```iterators```. ```set``` has no ```.at()``` or ```[]``` syntax.

Unlike ```vector```, ```set``` containers are always sorted on their contents.

Unlike ```vector```, ```set``` containers can hold at most one instance of particular value.

# Iterators

You are accustomed to this:

```c++
	vector<float> f = { 1.0, 2.0, 3.0, 4.0 };
	for (size_t i = 0; i < f.size(); i++)
		cout << f.at(i) << endl;
```

Many containers offer ```iterators``` which for technical reasons can be preferable to direct indexing. For some containers like ```set``` the only way of accessing data in the container is by ```iterator```.

```c++
	for (vector<float>::iterator it = f.begin(); it < f.end(); it++)
		cout << *it << endl;
```

This loop does exactly the same thing as the previous loop. Notice how an ```iterator``` is declared. Two colons and the word ```iterator``` are preceded by the same type as the container.

```f.begin()``` returns an ```iterator``` for the first float in the vector. 

```f.end()``` returns an ```iterator``` for a place in the vector that is one place beyond its last entry. That's why you see the use of the "less than" operator.

Notice how the value of the ```iterator``` is accessed - using a pointer dereference.

Declaring ```iterators``` can be a lot of typing so C++ Version 11 added the ```auto``` keyword.

```c++
	for (auto it = f.begin(); it < f.end(); it++)
		cout << *it << endl;
```

This loop is the same as the previous one, with less typing.

# This project

## Overview

You're keeping track of whether or not you've seen certain symbols. The initial symbols *can* come from a file but then the user can add and delete more symbols interactively.

The symbols have to pass some tests to be considered valid. If they're not valid, they can't go into the set.

## Starter code

In this project you can begin with some starter code. 

```c++
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <set>

/* Your name
   Project one
   CSC 1120 - Spring 2018 - Prof. Kivolowitz
*/

using namespace std;

bool ValidateSymbol(string s)
{
   // Your code
}

void PrintMenu()
{
   // Your code
}

void List(set<string> & m)
{
   // Your code
}

bool GetInput(set<string> & m)
{
   // Your code
}

void Add(set<string> & s)
{
   // Your code
}

void Delete(set<string> & s)
{
   // Your code
}

int main()
{
   // Your code
   
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
```

## ```GetInput```

If you give your program a command line parameter, call this function to read lines, validate symbols and insert if allowed.

Print an error if the file cannot be opened.

Print the size of the set after reading all the lines.

These are the things this function can produce. Variable names are up to you (and of course, these lines are not in orderor are they back-to-back in sequence).

```c++
	cout << "File: \"" << s << "\" could not be opened for reading." << endl;
	cout << "Set size is: " << m.size() << endl;
```

## ```ValidateSymbol```

This function returns a boolean as to whether or not the symbol should be added to the set.

You may write your project on the Mac or on Windows but the zylab will be graded on Linux. There are differences between these computers in how they handle the end of a line of text. Please make use of this next bit of code:

```c++
		size_t p = s.rfind("\n");
		if (p != string::npos)
			s.erase(p);
		p = s.rfind("\r");
		if (p != string::npos)
			s.erase(p);
```

The above code looks for the presence of line feeds and carriage returns and, if found, removes them.

You need to distinguish between letters and numbers. Use ```isalpha```. This function can be found online and also by searching your zybook.

## ```PrintMenu```

This is the expected output of this function.
```
Enter command (quit exits): help
help - prints this menu
list - prints symbols
count - prints number of symbols
add - ask for symbol to add
delete - ask for symbol to remove
```

## Operation of remainder of the program

### Example of being unable to open a file (command line argument)

```
File: "does_not_exist.txt" could not be opened for reading.
Exiting.
```

### Loading a file with bad symbols then quitting (command line argument)

```
Skipping "1test" because first character is not alphabetic.
Skipping "te st" because of bad character.
Skipping "te$st" because of bad character.
Set size is: 0
Enter command (quit exits): quit
Exiting.
```

The ```Skipping``` messages are coming from ```ValidateSymbol```.

### Reading some good symbols then listing the contents of the set (command line argument)

```
Set size is: 3
Enter command (quit exits): list
1....Foo
2....i
3....index_counter
Enter command (quit exits): quit
Exiting.
```

### Reading symbols then what can come from attempting to add (command line and manual)

```
Set size is: 3
Enter command (quit exits): add
Enter symbol: bad symbol
Skipping "bad symbol" because of bad character.
Enter command (quit exits): add
Enter symbol: good_symbol
Symbol added.
Enter command (quit exits): add
Enter symbol: good_symbol
Symbol NOT added.
Enter command (quit exits): quit
Exiting.
```

Notice the second time ```good_symbol``` is added, it is rejected because it is already there. The ```.insert()``` method returns a templated ```pair```. In this case, the pair's ```second``` field is a boolean that says if the insert actually happened.

Some sample code using our new friend ```auto```:

```c++
	auto r = s.insert(line);
	if (r.second)
		cout << "Symbol added." << endl;
	else
		cout << "Symbol NOT added." << endl;
```

### Using the list and delete command

```
Enter command (quit exits): list
1....Foo
2....i
3....index_counter
Enter command (quit exits): delete
Enter symbol: Foo
Enter command (quit exits): list
1....i
2....index_counter
Enter command (quit exits): delete
Enter symbol: Foo
Symbol not found.
Enter command (quit exits): 
```

# Handing in

The usual way on elearning.

