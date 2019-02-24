# Frankenmap

All the words from Mary Shelley's *Frankstein or The Modern Prometheus* have been munched down to one word per line with all punctuation removed. You are going to use a giant ```map``` to record the number of times each word appears as well as keep track of every line number in which each word appears. Once your data structure is made, you will allow a user to interactively query your database.

A ```shell script``` is also provided to allow you to double check that you have at least found every word a correct number of times.

# Sample output

## Failure to supply a file name

```
$> ./a.out
Must provide word file name.
```

## Providing a bad file name

```
$> ./a.out BADFILE
Could not open: BADFILE
```

## Providing Frankstein's data

```
$> ./a.out words.txt 
Enter a word (case sensititive): date
date found 5 times on lines:
9771, 19637, 20065, 76921, 78077
Enter a word (case sensititive): Date
Date found 1 times on lines:
69
Enter a word (case sensititive): bananas
Could not locate: bananas
Enter a word (case sensititive): 
$>
```

What you see above shows the "date" with lowercase "d" is found 5 times in the whole of the book. It is found on the indicated lines (numbering from 1). "Date" with an uppercase "d" is found but once on the indicated line. Yes! We have no "bananas".

[Yes! We have no bananas](https://www.youtube.com/watch?v=PDd8shcLvHI)


## Checking results

```
$> ./check.bash Date
       1
$> ./check.bash date
       5
$> ./check.bash bananas
       0 
```

# Maps

Maps are a powerful type of data structure which allow very fast searching for keys to find their associated values (a *key / value pair*). The idea is "this *key* maps to that *value*."

Maps are described in chapter 14.4 of your book.

# Features of maps used in this project

## Defining a map

Assuming:

```c++
#include <map>
```

```c++
map<key_type, value_type> map_name;
```

### Our value type

```c++
class Node {
public:
        Node() 
        {
              frequency = 1;
        }

        int frequency;
        vector<int> appears_on_lines;
};
```

Notice the ```vector<int>```. Use this to record the line numbers on which each word is found.

## Our map

```c++
map<string, Node> words;
```

## Adding to our map

Assuming ```n``` is a ```Node``` and ```a_word``` is a ```string```:

```c++
words.emplace(a_word, n);
```

Notice this isn't a ```push_back```. Maps don't have a "front" or a "back" per se. In fact, when we add a key / value pair to a map, it isn't clear *where* the new entry goes. We don't need to know (at this point).

Note that you must, in this project, add a key / value pair only if the key was not already in the map. 

## Finding an entry in a map

Here is some illustrative code:

```
auto it = words.find(word);
if (it == words.end()) {
       // Could not be found
} else {
       // key was found
}
```

The ```find``` method will return an iterator to a *pair* if the key is present. Otherwise it returns an iterator to the *end* iterator of the map.

Pairs are discussed in chapter 14.3 of your book. The iterator returned by ```find``` provides two members: ```first``` and ```second```. Recall:

```c++
map<string, Node> words;
```

This says in our case, ```first``` will be a string and contains the key. ```second``` is a ```Node``` and contains the value.


## Deallocating our map

There isn't any dynamic memory allocation in this project so deallocation takes place automatically. valgrind is not used in this assignment.

# Partner rules

You may use a partner.

# Suggestion

Make your own test data files. A first file might have only one word. A second file might have the same word twice.

----

<i>You're building a tall building. Don't move on to the next floor until you are sure of the current floor.</i>

----


# Academic integrity guidance

Talk but don't look. Describe but don't show.

# Grading

Out of 100 points, as usual. 

# Dates

Assigned 25 February. Due 4 March.



