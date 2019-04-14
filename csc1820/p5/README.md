# Retro Fireworks

C++ is an example of an object oriented programming language which provides a behavior called *polymorphism*. Polymorphism is when more than one function or method with the same name can be called to produce different results.

You have seen a kind of polymorphism in the past when you have overloaded functions or operators. This is *static polymorphism*. This is known as *early binding* because the choice of which implementation to use is made at compile time.

Another type of polymorphism works in conjunction with *inheritance*. When one class inherits from another the *subclass* becomes a specialization of the *base class*.

Given:

```c++
class Base {
public:
	Base();
	int foo;
};

class Sub : public Base {
public:
	Subclass();
	int bar;
}
```

one can say that ```Sub``` **is a** ```Base``` that has what ```Base``` has plus an integer named ```bar```. 

The notion of **is a** is the distinguishing characteristic differentiating derived classes from subclasses.

# Curses

In this project you will use the curses library. The curses library is called from your code and linked to your object code by the linker. If you are using a project made from my script, there is nothing you need do for the link step.

A minimal curses program that initializes curses then takes it down is:

```c++
#include <curses>

int main()
{
	initscr();
	endwin();
	return 0;
}
```

This program will compile and link with curses and when run, appears to do nothing. 

A critical thing to understand about curses is that it uses *double buffering*. Double buffering (even quad buffering) is heavily used in computer graphics whereby two logical screens are used, the front screen and the back screen. While the front screen is being displayed, drawing takes place in the back screen. When the back screen is complete, it is swapped for the front screen. Then, the former front screen is used as the current back screen and is used for drawing. 

The back screen is used to accumulate what will be shown to the user *next*.

Curses was created at a time when users using dial-up modems received only about 30 to 120 characters per second. Given that a terminal provided 80 columns by 24 rows (1920 characters) receiving 30 per second meant a full screen would take 64 seconds to update!

The curses package was created to finely optimize (reduce) the number of characters that needed to be transmitted. It did this by accumulating the *next* screen in a back buffer and then comparing it to the front screen. Only the differences were transmitted.

Many classic (now considered retro) user interfaces were created using curses. Curses even supported windows!

Due to double buffering, no screen changes take place until you called the ```refresh()``` function. Here is a program that clears the screen, draws a border then waits for 5 seconds before exiting.

```c++
#include <curses.h>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
	initscr();
	erase();
	box(stdscr, 0, 0);
	refresh();
	this_thread::sleep_for(chrono::seconds(5));
	endwin();
	return 0;
}
```

If the ```refresh()``` were left out, the program would appear to do nothing. Run the above program from the command line having compiled it thusly (assumes the code is in main.cpp).

```
g++ main.cpp -lcurses
```

```initscr()``` initializes the internal state of curses and creates a standard "screen" called ```stdscr```.

After ```initscr()``` has been called, two integer variables defined by curses become valid. These are ```LINES``` and ```COLS```. These tell you how big the standard screen is.

The following program puts ```hello world``` centered on the screen.

```c++
#include <curses.h>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
        initscr();
        erase();
        box(stdscr, 0, 0);

        string hw("hello world");
        mvaddstr(LINES / 2, (COLS - hw.size()) / 2, hw.c_str());

        refresh();
        this_thread::sleep_for(chrono::seconds(5));
        endwin();
        return 0;
}
```

The function ```mvaddstr()``` is a combination of ```move()``` and ```addstr()```. Notice is takes the y coordinate first, then x. That is, it takes the line number first then the column number.

Lines are numbered from 0 (being the topmost screen line). Columns are also numbered from 0 (being the leftmost column).

Here is a link to a tutorial on curses:

[NCURSES Programming HOWTO](http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/)

Here is another tutorial - more complete:

[Writing programs with curses](https://invisible-island.net/ncurses/ncurses-intro.html)

Here is a complete curses manual:

[curses manual](https://invisible-island.net/ncurses/man/ncurses.3x.html)

## sleep_for()

There are two interesting include files shown above (and next):

```c++
#include <thread>
#include <chrono>
```

A ```thread``` is a something that is executing right now. We don't need to know the details for now. 

The include file ```thread``` gives you access to ```this_thread```. ```this_thread``` is your executing program. It's "you."

One of the things you can ask of your own thread is to have it pause for a specified amount of time. This is the purpose of ```sleep_for```. ```sleep_for``` must be told how long to pause. This is the purpose of ```chrono```.

Without the call to ```sleep_for``` in the main loop, the animation may be to fast to see let alone appreciate.

## chrono

The ```chrono``` include file gives you access to a means of specifying time periods in a way that is independent of your operating system and is easier to understand that previous methods. Time periods are interpreted as being in the units of time that you choose. Each of the following specifies 1 second:

```c++
chrono::seconds(1);
chrono::milliseconds(1000)
chrono::microseconds(1000000)
```

# This project - retro fireworks

In this project you will create a base class called ```Rocket``` which knows how to fly and draw a simple rocket. Then, you will define a set of defined subclasses that specialize ```Rocket``` to create different behaviors.

## main()

Please see [here](./main.md) for a description of the main program file (given to you).

## Fleet class

Please see [here](./fleet.md) for a description of the Fleet class. You must implement this class.

## Rocket class

Please see [here](./rocket.md) for a description of the Rocket class. You must implement this class.

## Derived classes

Please see [here](./derived.md) for a description of the classes derived from Rocket. You must implement these classes.

## Learning a little more about Class Access Modifiers

You have seen ```public``` and ```private```. These are access modifiers. There are in fact three access modifiers:

| name | meaning |
| ---- | ------- |
| public | Members and methods marked public are accessible by all code in the program. |
|protected | Members and methods marked protected are accessible only by the class itself and any subclasses |
|private | Members and methods marked private are only accessible by the class itself. |

When inheriting from a base class, there are also access modifiers as in here:

```c++
class Streamer : public Rocket
```

This usage determines how to treat members and methods from the base class. 

| name | meaning |
| ---- | ------- |
| public | The access modifiers of members and methods of the base class are preserved. |
|protected | Public members in the base class are treated as protected members of the derived class. |
|private | Public and protected members of the base class are treated as private. |

The following is taken from [here](https://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance).

```c++
class A 
{
public:
    int x;
protected:
    int y;
private:
    int z;
};

class B : public A
{
    // x is public
    // y is protected
    // z is not accessible from B
};

class C : protected A
{
    // x is protected
    // y is protected
    // z is not accessible from C
};

class D : private A    // 'private' is default for classes
{
    // x is private
    // y is private
    // z is not accessible from D
};
```
## Setting the initial up force (argc / argv)

Use a default up force of 4 +/- 0.5. If ```argc``` is greater than one, attempt to convert ```argv[1]``` to a float and use it as the initial up force. Being able to adjust the up force is needed to allow for console windows that are tall or not. An up force that is too large will launch rockets above the top of the window. No fun in that.

# Exiting the program

The program must run until you quit it by typing CNTRL-c. That is, hold the CONTROL key and the 'c' key at the same time.

# Use of dynamic memory allocation

Notice the use of pointers to class instances. You must not leak memory. This program *doesn't end* so using ```valgrind``` isn't an option but I will be inspecting your code for proper use of ```delete```. Whenever a rocket ages out, it should be deleted (and removed from the vector of rockets - see next).

# Problems iterating over the vector of rockets

Your main loop will iterate over the existing rockets. But, more rockets may be added while you're doing this (because of age-related triggering). You must not iterate over the new rockets. This is the reason for the vector of Rocket pointers being passed around. New particles are appended to the ```Fleet``` vector of Rocket pointers **after** you've completed iterating over that vector.

Also, when you cull the rocket vector of aged-out rockets by calling erase you must do so carefully lest you lose your place in the vector. A very specific hint is to use ```iterators``` and the return value of ```erase()```. 

# Suggestion

Delay writing and testing any derived classes until your Rocket class is working perfectly.

Then write one derived class, not all of them. The birthing code can be modified later to handle choosing from all of them later. Until all your subclasses are tested, just launch only one type of rocket (the one you're testing).

# Partnership rules

You may have a partner in this project.

# Extra credit

I rarely offer extra credit. However ...


Five points of extra credit will be awarded to those who go beyond this specification to include their own type of firework subclass.

Five points additionally will be award to the *one* project that has the most interesting or coolest extra firework as decided solely and exclusively by me.

# Note

This might be the biggest project in your young careers. Approach it as such with respect and trepidation. We will implement small parts of this together but do not believe you can coast - there is much work here. Fun work. The best kind.

Remember, the world's top scientists did the following for years:

![boom](./rocket.gif)

