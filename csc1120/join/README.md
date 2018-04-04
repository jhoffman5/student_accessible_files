# join

This project packs a lot of knowledge in a small package. At the highest level, you'll be learning a basic concept from CSC 2810 - Database Design and Management: the *join*.

[EF Codd](https://en.wikipedia.org/wiki/Edgar_F._Codd) invented the formalism of the *relational database* model. A rational database is at its heart something you have seen IRL and to which you can relate (unintentional pun).

Imagine a table where each row of the table is a collection of data about the same *thing*. We have done this when we create and array or vector of ```struct```. Each column of the table is a different data member or ```field``` in the row. This picture of a table is so apt, the relational model actually calls each set of data a table. Each row of the data is a ```record```, logically similar to individual structs making up the rows.

The relational model derives a lot of power from how multiple tables ```relate``` to each other. For example, one table may contain customer names, id numbers and addresses. Another table might contain id numbers and then also a date and amount of a purchase. Take together, you might put them into the same table but there is a *many* purchase to *one* customer relationship. 

If the the information in both tables were mushed together, then all the address information would have to be duplicated for every purchase. This doesn't make sense for multiple reasons. First, the added data storage requirement and second the opportunity for error if the address of the company changes.

Notice in the above description both tables store a customer id. We can think of the id as a ```key``` that relates each customer to their purchases. Given a name, you can look up an id. Given the id you can look up all their purchases. Etc.

# Partnership Rules

We are using the following work rules:
- You may partner with whomever you choose.
- You may choose not to partner.
- You may work (share code) with one and only one person (your partner).
- You may organize help groups in any fashion you wish to discuss, draw pictures, research, etc.
- You may not use a projector to project code or otherwise share code outside of your partnership.
- Partners receive the same grade as each other.
- Only one person in a partnership will submit code.
- Your code *must* indicate who your partner is at the top of your main source file.

# This project

In this project you will create a database (in memory using associative container data structures). You'll need your csv file reading code from the ```maps``` project and your safe float processing code from the ```stack``` project.

You are supplied two data files. These data file names are specified to the program one the command line. By now, you should be expert at this.

## Regarding csv files

**csv files are text files!** Yes, Excel can read csv files. Do not create or edit them there. **They are text files - edit them with a text editor.**

## company.csv

This file defines your customer table. Each of the 100 lines contain an id number, name and full address of a real sound but totally ficticious company. Here is an example:

```
00000003,COMPARABLE TONIGHT INCORPORATED,4221 UNNAMED 115,CARMEL,IN,46032
00000004,DESCRIPTIONS ASHLEY INCORPORATED,7099 FAIRBANKS ST,INDEPENDENCE,MO,64057
00000005,LORD CASE CO,5533 BATTERY EAST RD,UPPER GWYNEDD,PA,19446
```

## data.csv

This file contains a record for each purchase made by customers. There are 1000 of these records each containing four fields: customer id, invoice number, date and amount.

*Of these fields, only the invoice number is unique. In this project we are NOT making use of this information.*

For now, what matters is that the customer ids found in data.csv match those found in ```company.csv```. The same customer can have an arbitrary number of purchases.

Here is a sample:

```
00000002,00000003,5/7/2017,688.75
00000024,00000004,12/15/2017,657.46
00000024,00000005,12/28/2017,42.65
00000072,00000006,11/9/2017,41.54
00000060,00000007,9/22/2017,548.06
```

# Goal

Produce a report that prints the accumulated total of all purchases made by each company, printed in alphabetical order (by company name).

Here are the first few lines *of what your output should look like*:

```
File: company.csv contained 100 records.
File: data.csv contained 1000 records.
Sales summary report:
=====================
ID:       Name:                                   State:  Purchases:    Total:    
00000078  ADVANCE NICHOLAS BANK                   LA      11            $5,962.62  
00000082  AGREED CUSTOMERS LLP                    IA      10            $5,838.23  
00000001  ALPINE SIGNING LTD                      MA      8             $3,717.76  
00000043  AMAZON THRESHOLD LLP                    SD      11            $3,394.20  
00000089  AMONG THONG INC.                        NJ      9             $4,637.81  
00000099  ANGLE SUITE LLP                         MI      14            $7,096.84  
00000098  APPLICATIONS PROTEIN INC.               TX      9             $4,180.15  
00000054  ASSISTED DISEASE LTD                    WV      8             $5,546.21  
00000073  BATHROOMS LAURA LTD                     AE      10            $5,165.83  
00000012  BIBLE BETH INC.                         WI      8             $2,394.38  
00000008  BIBLIOGRAPHIC ETHNIC LIMITED            IL      13            $5,420.62  
00000086  BUFFALO YOUR CORP                       IA      13            $6,064.00  
00000000  BUNNY BRADFORD LTD                      NY      15            $7,662.72  
00000064  CALCULATORS STRENGTH LLC                CA      10            $5,149.54 
```

While your formatting might vary slightly from this, the contents of your report must match this content exactly to be correct.

# Data structures

We will use two ```maps``` and one ```multimap``` in this project. 

Remember that a ```map``` sends a key to a matching value. The ```maps``` needed are:
* sending company id to company details
* sending company name to company id

A ```multimap``` is like a ```map``` except that a key can pair up to mulitiple values. In this program, the purchases file may contain any number of records from the same company id. So, company id is used as a key to find puchases made by that company. One company id leads to multiple purchase records (hence ```multimap```).

```maps``` are kept in sorted order. 

The second ```map``` sending company name to company id is used as a way to enumerate the first ```map``` in company name sorted order. That is, the first ```map``` keeps the whole company detail (sorted by id) while the second map allows rapid indexed access to the same data but in alphabetical by company name order.

# Algorithm

Behold the power of relating tables:
* For each name in the second map, get a company id. This gets company ids in alphabetical order.
* Using that company id, look up the right company detail to get the state.
* Using that company id, sum up *all the purchases made by that id*.

The records in the purchases ```multimap``` corresponding to one company id can be singled out using the ```equal_range``` method provided by ```multimaps```.

# Separating / structuring your project into multiple source and include files

This project gives you a nice opportunity to split your project into multiple source and include files. For example, you might have a seperate class (or at least set of functions) that deals with the customer file and another that deals with the payments file. Both will use a split function: please do NOT duplicate this code. In my solution I chose to have four source code files and three include files.

To give you and *idea* of where to start, here are my include files. You do not have to use these. *What is important, is that you use two maps, one multimap and produce the right results*.

My ```customer.hpp```:

```c++
#pragma once
#include <map>

class Customer {
public:
    Customer();
    Customer(std::string id, std::string name, std::string street, std::string city, std::string state, std::string zipcode);

    static bool LoadCustomers(std::map<std::string, Customer> & ctable, const char * filename, bool verbose = false);

    std::string id;
    std::string name;
		std::string street;
		std::string city;    
		std::string state;
    std::string zipcode;

    static const int tokens_to_expect;
};
```

The ```#pragma once``` prevents this include file from being processed more than once even if it is included multiple times. It is processed by the preprocessor, of course. You can tell this because of the leading pound sign.

You know by now that a ```class``` differs from a ```struct``` in that all members default to ```private```. That's why there is the keyword ```public``` at the start of this class.

There are two constructs. One makes a blank Customer, the other makes an initialized Customer.

There are two uses of the keyword ```static``` here. As you know, every instance of a ```class``` or ```struct``` has its own version of every member. When a member has the keyword ```static``` in front of it, it means all instances *share the same member*.

I am not explaining much more about this include because
a) You are free to come up with your own design.
b) It's time.

Here is my ```purchases.hpp```

```c++
#pragma once
#include <map>

class Purchase {
public:
	Purchase();
	Purchase(std::string id, std::string invoice, std::string date, float amount);

	static bool LoadPurchases(std::multimap<std::string, Purchase> & ptable, const char * filename, bool verbose = false);

	std::string id;
	std::string invoice;
	std::string date;
	float amount;

	static const int tokens_to_expect;
};
```

Notice ```#include <map>``` is found here too. Don't worry. It has its own version of ```#pragma once```.

Here is my ```split.hpp``` because I put my split function into a separate file.

```c++
#pragma once

#include <vector>
#include <string>

void Split(std::vector<std::string> & tokens, std::string & line, std::string & delimeter);
```

Notice this include file also includes ```vector``` and ```string```. This is because these types appear in the signature of ```Split```.

Notice ```vector``` and ```string``` are fully qualified with ```std::```. This is because we cannot count on the user having entered ```using namespace std``` when this include file is included.

To ensure that we're all working with working ```Split``` functions, here is mine. It goes in ```split.cpp```:

```c++
#include "split.hpp"

using namespace std;

void Split(vector<string> & tokens, string & line, string & delimeter) {
	tokens.clear();
	size_t pos;
	while ((pos = line.find(delimeter)) != string::npos) {
		tokens.push_back(line.substr(0, pos));
		line.erase(0, pos + delimeter.length());
	}
	if (line.length() > 0) {
		tokens.push_back(line);
	}
}
```

# Suggested program flow

You can define your own program flow because by now you know how.

I suggest the following:
1. Ensure the right number of command line arguments.
2. Use these to load the customer file and the payments file. If these produce any errors, you should say so and quit.


# Data files

Are [here](./company.csv) and [here](./data.csv).















