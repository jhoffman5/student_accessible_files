# Introducing math and random numbers

## Summary

In this project, you will use math and random numbers to calculate PI badly.

The idea is that you will throw darts (i.e. make random combinations of an X and Y value) within a unit square. This means each X and Y coordinate will be between 0 and 1 inclusive.

Given a dart, compute how far it is from the origin using the Euclidean distance formula.

If the distance of the dart from the origin is 1 or less, count the dart as a *hit*. Of course, hits start at 0.

After a specified number of dart throws, divide the number of hits by the number of throws. This is the ratio of darts thrown that landed within a unit circle.

## Gotchas

There will be a number of instances where you have to convert ```int``` to ```float```.  Your book describes how to do this in section 2.11. In particular, pay attention to participation activity 2.11.6.

## Includes

You will need the following include files:

| file | why? |
| ---- | ---- |
| ```<iostream>```| This include gives you access to console input and output. |
| ```<cmath>``` | This include gives you access to lots of the usual math functions. |
| ```<ctime>``` | This include gives you access to a function that returns a time value. |

## Random numbers

Random numbers are an important part of computer science. They are the basis of most if not all simulations. Specifically random numbers are often used to simulation natural outcomes. In the case of the project, the natural outcome being simulated is where a dart will land.

The function ```rand()``` and its sibling ```srand()``` are described in section 2.18 of your book.

```rand()``` returns an integer between 0 and ``RAND_MAX```. ```RAND_MAX``` differs on 32 bit and 64 bit machines with Macs differing still more. Fortunately, we're all on our VM so the exact value of ```RAND_MAX``` doesn't matter.

This is an example of abstraction using **constants**. ```RAND_MAX``` has a value, but we don't need to bother with knowing what it is. Constants are good. The number 7 is a constant. But if 7 had a specific purpose, it's a **magic number**. For example is 7 meant *lucky* we should give it a name rather than repetitively using the literal 7.

For example:

```c++
const int LUCKY_NUMBER = 7;
```

This shows a pair of good practices. The name of constants is, by convention, put in ALLCAPS. Second, the number 7 isn't a **magic number** any more. It is clear what it is, it's your lucky number. Your lucky number might appear in many places in your code. Wouldn't it be a shame if someday you felt that 11 was your *new* lucky number? If you wrote literal 7's all over your code, you would have to find and change all instances. If you make a lucky number constant, all you have to do is change the constant in one place. Done!

The *qualifier* ```const``` says the variable ```LUCKY_NUMBER``` cannot be changed once it is set. If you try to change it, the compiler will flag that line with an error.

```RAND_MAX``` is such a constant (but implemented using an older method - the previous point is still the same).

You will need a function that returns a float between 0 and 1. This is a place where 2.11.6 will be important.

### Getting a random number

Simply calling ```rand()``` returns a random number in the range described at length above. Each time ```rand()``` is called, you get a different value.

### Getting *different* random numbers

The first time you call ```rand()``` every time your program runs, you will get the same value returned. That's not very random is it? The reason is that digital computers can't really manufacture random number in the truest sense of the word random. Instead, they generate pseudo-random values which, with care in writing the ```rand()``` function will not repeat in a very very long time. 

An earlier version of ```rand()``` repeated values after a shorter period than thought, causing decades of research results to be called into question. Ouch! In 1951, one of the great giants of computer science, John von Neumann,
said:

```Any one who considers arithmetical methods of producing random digits is, of course, in a state of sin.```

To ensure your program doesn't generate the same random sequence over and over, use ```srand()``` to *seed* the random number generator. If you use the time-of-day as the seed, you will get what appears to be a different sequence every time. See your book section 2.18.

## Doing math

The include ```<cmath>``` gives you access to lots of math functions including ```sqrtf```. This function returns the square root of its argument as a ```float```. ```sqrt()``` returns the same as a ```double```.

```<cmath>``` also gives you ```M_PI```, the "correct" value of PI. Use this in your final printed output. See below.


## Specifying whether a floating point literal is a float or double

```double``` is a floating point type like ```float``` except it has far higher precision. In the time since the big bang, a float has enough precision to keet track of every 1000 years. A double could count the number of minutes.

Even on today's computers, there are reasons to use ```float``` rather than ```double``` (speed and space). For numeric literals how can you tell the various number formats apart?

| Number | Its type |
| ------ | -------- |
| ```4``` | an integer |
| ```4.0``` | a ```double``` |
| ```4.0f``` | a ```float``` |

## Number of darts

See the discussion about **magic numbers** above. The number of darts to throw should be expressed as an appropriately named constant. Once your program works, try comparing 1000 darts to 9999999 darts.

## One final thought on the math

You know that ratio discussed above? You're working with only a quarter of a circle, so you have to multiply the ratio by ...

## Sample output

When the number of darts is coded to 1000:

```
Number of darts: 1000
A Monte Carlo derivation of PI is: 3.244
The "real value" is: 3.14159
```

When the number of darts is coded to 9999999:

```
Number of darts: 9999999
A Monte Carlo derivation of PI is: 3.14139
The "real value" is: 3.14159
```

## Remember

Your name must be at the top of your program.

There are no partners in this program.

Hand in your code only (the .cpp file).
