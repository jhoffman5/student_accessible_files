# Milestone 1 - Inventory (structs / classes)

This is a two part project providing lessons on two exciting and substantial sets of new learning:

* structs / classes
* file input

In this first milestone, you will create an inventory class with members and methods. This is the structs / classes part. 

In the next project, you will extend this project (so it better be right) to:

* read the inventory from a data file
* interactively present a menu of items
* accept orders 
* make change.

# Discussion

## Things in inventory

A vending machine vends things. The machine must have knowledge of the things it vends. 

For example, information related to one item might include:
* Item name
* Item location
* Item cost
* Item quantity on hand
* Item contains nuts

## ```class``` and ```struct```
When you have various information about the same *thing* it makes a lot of sense to place that information in the same *thing*. You're creating an object with a custom type - a collection of information in one handy bundle.

The object (the bundle) is called a ```class``` or ```struct```. Classes are the same as structs with one exception - the default *protection*. *Protection* divides programmers apart into those that have access to all of the object and those that have limited access to the object.

Something inside a ```class``` or ```struct``` that is marked ```public``` is accessible to everyone. This is the default for ```struct```. For ```class``` the default is ```private```. ```private``` means that data or functions with this marking are accessible only inside the ```class``` or ```struct```.

When you choose one or the other is a discussion left for later in the course. For now, let's assume everything is ```public```. As such, we can use ```struct``` in this project.

Here is a non-compilable but generic ```struct``` definition:

```c++
struct NAME
{
	NAME();
	TYPE member_variable_1;
	TYPE member_variable_2;
	TYPE Method_1();
	TYPE Method_2();
}
```

Here is an actual ```struct``` definition:

```c++
struct FrozenFood
{
	FrozenFood(string pname, string mname, int qoh);
	
	string product_name;
	string manufacturer_name;
	int quantity_on_hand;

	bool Sell(unsigned int quantity);
	int QuantityOnHand();
	void Restock(unsigned int quantity);
}
```

This ```struct``` has three data *members*: ```product_name```, ```manufacturer_name``` and ```quantity_on_hand```.

Being a member of an object means that it is a variable associated with that object.

This ```struct``` has three *methods*: ```Sell()```, ```QuantityOnHand()``` and ```Restock()```.

A method is simply a function embedded in an object. When the method is being executed, it has complete knowledge of exactly one instance of the object.

## Your own include files 

Notice there is no code for the methods. Just their *signatures*. This allows the structure declaration to be placed into its own include file without the code - keeping the code hidden in its own source code file. 

This is a Good Idea.

Here is what the complete include file (perhaps named ```frozen_food.hpp```) might look like:

```c++
#pragma once
#include <string>

struct FrozenFood
{
	FrozenFood(std::string pname, std::string mname, int qoh);
	
	std::string product_name;
	std::string manufacturer_name;
	int quantity_on_hand;

	bool Sell(unsigned int quantity);
	int QuantityOnHand();
	void Restock(unsigned int quantity);
}
```

You should begin all your own include files with ```#pragma once```. This will be explained in class.

To make the include file stand on its own, notice I have included ```<string>``` because ```string``` variables are used in the declaration. Notice the use of ```string``` is preceded by ```std::```. 

Normally you don't do this because you place:

```c++
using namespace std;
```

at the top of your programs. Notice that is **not** in the include file. The reason will be discussed in class.

# Implementation of ```class``` or ```struct```

So where is the code? The code is in a source file file of its own. Including the source code for only one ```class``` or ```struct``` in any files is a Good Idea.

Here is what ```frozen_food.cpp``` might look like:

```c++
#include "frozen_food.hpp"

using namespace std;

bool FrozenFood::Sell(unsigned int quantity)
{
	bool retval = false;
	if (quantity_on_hand >= quantity)
	{
		quantity_on_hand -= quantity;
		retval = true;
	}
	return retval;
}

int FrozenFood::QuantityOnHand()
{
	return quantity_on_hand;
}

void FrozenFood::Restock(unsigned int quantity)
{
	quantity_on_hand += quantity;
}
```

## Constructor

There is one method I have not discussed yet:

```c++
	FrozenFood(std::string pname, std::string mname, int qoh);
```

This is called the *constructor*. See chapter 7.7 in your text. Constructors are special - one is **always** called. If you write one (or more) of your own, one will be called. If you don't write one, a default constructor will be provided for you.

Notice two things about the constructor:

1. It has no return type.
2. It has the same name as the ```struct``` or ```class```.

Constructors are used to construct the initial contents of the object.

Let's add the code for the constructor onto the end of ```frozen_food.cpp```.

```c++
FrozenFood::FrozenFood(string pname, string mname, int qoh)
{
	product_name = pname;
	manufacturer_name = mname;
	quantity_on_hand = qoh;
}
```

Notice ```std::``` was not necessary. Remember why?

## Item ```struct``` members

These are the data members:

| Member     | Type      |
| ---------- |:----------|
| name       | string     |
| location   | string     |
| cost       | integer<sup>*</sup>   |
| quantity   | integer    |
| has_nuts   | bool |

```cost``` is an integer because it will represent the integer number of pennies the item costs. You will have nickles, dimes and quarters  in your available change (next project).

## Item ```struct``` methods

You will need methods with which to manipulate individual things in inventory such as:

| Method | Purpose |
| :----- | :------ |
| GetCost | provides "secure" (read-only) access to the cost field |
| GetName | provides "secure" (read-only) access to the name field |
| GetLocation | provides "secure" (read-only) access the location field |
| InStock | returns a bool indicating if quantity is above zero |
| HasNuts | returns a bool indicating if the item has nuts |
| Vend | deducts one from inventory - returns a bool saying if successful |

Of course, you will also need a constructor (accepting values for all members).

## The Inventory

A collection of individual things does not an inventory make. You'll need another data structure that collects the individual items together into a collection of items.

A ```vector``` seems like a good choice.

```c++
vector<Item> inventory;
```

The above assumes you named your ```struct``` Item.

## The program

You will write your own custom type to represent items with the specification provided above (all data members and methods).

You will initialize an inventory with two or more items. Sample code might look like:

```c++
inventory.push_back(Item("Zagnuts", "A1", 150, 10, true));
inventory.push_back(Item("GoodnPlenty", "A2", 125, 2, false));
```

You will write unit tests for every method you write.

A unit test is a test of a limited function set that identifies correct and incorrect operation. For example, a unit test for ```GetCost()``` might look like this:

```
Testing Item::GetCost
inventory[0].GetCost() returns 100
should return 150
FAILED
```

This test failed because ```inventory[0]``` is Zagnuts and they cost $1.50.

Testing ```Vend()``` requires a little more work than testing a return code. Output might look like:

```
Testing Item::Vend true case
setting inventory[0] quantity to 1.
inventory[0].Vend() returns true
should return true
PASSED
Testing Item::Vend false case
inventoty[0].Vend() returns false
should return false
PASSED
```

Please ask if you have questions.

# What to hand in

Your source code and include files, if any.

# Grading

Out of 100 points.
