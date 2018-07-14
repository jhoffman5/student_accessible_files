**All repos must be private**

# ```map``` project

In this project you will use another *STL* container, the ```map```.

You will learn a number of things:
* ```map``` of course
* ```pair```
* You get to use *exceptions*
* Learn about processing *csv* files

# Not interactive

There are no menus in this project. If a data file is named as a command line argument it is read and processed to completion.

# *csv*

*csv* means comma separated value. Generalized, the comma could be replaced by other symbols such as the tab character. Here is an example:

```
foo,two,lou
far, car
bead, a seed, need, my dog I need to feed
```

The first line should resolve into 3 *tokens* of "foo", "two" and "lou". The second line should resolve into only two tokens. Notice that line one has no whitespace. Line two does. Line three has a lot of whitespace. Only commas matter. Line three solves into four tokens: "bead", "a seed", "need", "my dog I need to feed".

It is possible to encode commas in a token but this is more complex and is not covered here.

You will need to write a *tokenizer* which takes a whole line and returns a vector of strings where each string is one of the tokens separated by a delimeter (comma). Use ```string::find()```, ```string::substr()``` and ```string::erase()```. 

# Maps

Maps related keys to values in a pairing. The same key always leads to the same value. Maps are cool because you can work with them like arrays (kind of).

In this project you are creating a map from strings to floats. Sample:

```c++
map<string, float> m;
```

You can put something into the map or add to an existing member by:

```c++
m[tokens[0]] += n;
```

Above, ```tokens[0]``` is a string. If it didn't exist in the map, it is created and initialized with 0. Then the value of ```n``` is added to it.

You can check to see if a key is in the map using ```.count()```

# Pairs

A ```pair``` is a templated type that pairs a ```first``` and ```second``` member together. Both have particular types. Often pairs are declared using the ```auto``` keyword. 

# Input

Specify the name of a text file as a command line argument. It should be a *csv* file.

It doesn't matter what the first token is (letters, numbers, etc), it is always taken to be the key (a string).

If there is a second token, it must be a number. That number is added to the previously existing value or as the first value for that key. If the second token is not a number an error message is printed then the line is ignored:

```
Second token must be a number.
```

If there is only a single token is given, the token is used as a key and it's value is accessed. Note, this should not cause a new pair to be added to the map. 

If more than 2 tokens are given, the input line is rejected with a message.

Given a file with this:

```
good, 21
goooood, 2
pretty good, -10
goooood
goooood, 202
pretty good, 11
```

The program should output this:


```
goooood             2.000000
Size of map: 3
good                21
goooood             204
pretty good         1
```

In the output above, 

```
goooood             2.000000
```

is printed because ```goooood``` appears on a line of input by itself.

You get:

```
pretty good         1
```

Because in the input is both of these:

```
pretty good, -10
pretty good, 11
```

The output starting with:

```
Size of map: 3
```

is what is printed after the whole input file is read. See next.

# How the programs ends

When the end-of-file is processed, ```getline()``` will return ```false```. Use this to end your input loop.

Then, print the number of elements in the map and then print out the keys and values found in the map. This container keeps the keys sorted. (There is also a container available that does not. The unordered map is faster for insertion.)

There are a number of ways you can iterate over the members of the map. You might use the ```iterator``` approach. The iterator will be of the map's associated pair type.

# Converting a string to a number safely (exceptions)

Remember the grief you suffered if you ever entered a non-number into this code:

```c++
float foo;
cin >> foo;
```

Let's figure out how to deal with this safely - and introduce exceptions.

Try this program (enter whatever else you need to give it a try):

```c++
int main() {
	float f = stof("Henry");
	return 0;
}
```

**Crash** An ```exception``` happens. Exceptions are typed error conditions. In this case it is a ```std::invalid_argument``` exception.

The use of exceptions is quite common in better programming and exceptions themselves can be fairly cool, complex and subtle. Here we introduce the barest minimum.

Try:

```c++
int main() {
	try {
		float f = stof("Henry");
	}
	catch (invalid_argument) {};
}
```

All is well.

Or try this:

```c++
int main(int argc, char * argv[])
{
	float f = 0.0;

	try {
		f = stof("Henry");
	}
	catch (invalid_argument) {
		cout << "invalid argument exception" << endl;
	};

	cout << "The value of f is: " << f << endl;
	return 0;
}
```

Remember scoping and braces. What are the implications?
