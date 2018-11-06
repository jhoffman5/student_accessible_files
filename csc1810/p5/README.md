# Chatty Vending Machine - MS 2

This project’s goal is to finish the chatty vending machine. This machine:

* Is very chatty, it tells the user all sorts of information.

* Is very thorough about checking for errors.

* Is able to accept payment and dispense change.

## Done so far

In MS1 you practiced:

* Creating a struct or class

* Putting struct or class declarations in a separate include file.

* Putting struct or class definitions in a separate C++ file.

* Writing unit tests

## What the program outputs

Let's jump right to what the program outputs and, in so doing, gain insight into what it does.

This is your main menu. It must be formatted exactly in this way.  Notice the precise colums and justification. This clearly is using ```iomanip``` for formatting. An appropriate place to implement an item's print-out is a new method to the Item class or struct you implemented in MS1.

The “Nuts” column indicates if the product contains nuts.

```
Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
B3  Planters Nuts            $0.75 *
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

Here is what a purchase looks like:
```
Make selection (or Q to quit): B3
Enter payment (No more than $5 and no pennies allowed): 1
Enjoy your Planters Nuts!

Change:
1 Quarters
0 Dimes
0 Nickels

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

Item B3 was selected. Its cost is 75 cents and the user submitted one dollar. Note the user’s change in 1 quarter. 

You must calculate the *largest number of each type of coin* and dispense these first when you make change. Notice the Planters Nuts were NOT printed in the second menu. That’s because we only had 1 unit and the user bought it. Items that are sold out do not print in the menu.

Here is what is printed when an item that is undefined or out of stock is selected:

```
Make selection (or Q to quit): Z4
Item not found or item out of stock.

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```
 
Here is what happens when you don’t give enough money:

```
Make selection (or Q to quit): A1
Enter payment (No more than $5 and no pennies allowed): 1
Amount tendered is insufficient

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

Your machine implementation rejected the sale of a Hershey Bar because the user tendered a payment which was not sufficient to cover the item's cost.


This is what happens when you give too much money (anything larger than 5 dollars in rejected).
```
Make selection (or Q to quit): A1
Enter payment (No more than $5 and no pennies allowed): 20
Amount too large. Take back your money.

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

Here’s what happens when you are due a lot of change:
```
Make selection (or Q to quit): C6
Enter payment (No more than $5 and no pennies allowed): 5
Enjoy your Milkyway!

Change:
14 Quarters
1 Dimes
1 Nickels

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

The machine is initialized with a pot of change, a certain number of each kind of coin. In making change, it will use the largest coin first. In order to make up the appropriate amount of change, you must break down the amount into quarters, dimes and nickles. Remember, the price of each item is always divisible by 5.

Making change *might* employ a loop, the mod operator, subtraction - maybe integer division and multiplication. Who knows?

Here is what happens when the machine runs out of one kind of coin but can still make change:
```
Make selection (or Q to quit): C6
Enter payment (No more than $5 and no pennies allowed): 3
Enjoy your Milkyway!

Change:
0 Quarters
16 Dimes
1 Nickels

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
B3  Planters Nuts            $0.75 *
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35

Make selection (or Q to quit):
```

Notice it gave out mostly dimes this time because the machine has run out of quarters to dispense. Again, the largest available coint is dispensed first.

Here is what happens if the machine cannot make change for your purchase:

```
Make selection (or Q to quit): A1
Enter payment (No more than $5 and no pennies allowed): 3
Sorry! We cannot make change for that amount. Take back your money.

Here is what is left in our coffer.
Change:
0 Quarters
0 Dimes
17 Nickels

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
B3  Planters Nuts            $0.75 *
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35

Make selection (or Q to quit):
```

Notice A1 costs $1.25 but the machine only has $0.85 left. Notice in this case, the machine prints exactly what it has left.
 
Here’s what happens if you enter an amount that isn’t a multiple of a nickel.

```
Make selection (or Q to quit): A1
Enter payment (No more than $5 and no pennies allowed): 1.26
Pennies are not allowed. Take back your money.

Key Product                  Cost  Nuts
A1  Hershey Bar              $1.25
C1  Snickers                 $1.50 *
C6  Milkyway                 $1.35
D3  Famous Amos Cookies      $1.75

Make selection (or Q to quit):
```

## Another struct or class

Your coffer of available change is to be another class or struct. 

* It must contain data members of an integer number of quarters, dimes and nickles.

* It must contain a constructor which takes the initial number of each coin to put in the coffer - set this to 20 of each coin for the machine's initial available change. You will use another instance to hold the actual change for a purchase, see next.

* It must contain a method which takes a reference to one of these classes or struct and returns a boolean. If the boolean is true, change was sucessfully made and the referenced struct or class breaks it down. If the method returns false, enough change was not available and the sale is canceled. The method must also take two more paramters: the cost of the item and the amount the customer entered.

To be reminded how to pass-by-reference, see chapter 6.8 of the zybook.

## Sorting the items

In the sample output the items are sorted by their key. You *do not* need to implement a sorting algorithm. Instead, if you add the Items to your inventory in sorted order, they will print in sorted order. Bottom line: sorted order *is not required.*

## Unit tests

You are *encouraged* to write unit tests for your new code but not required. If you write unit tests, do not enable them in the version of the code you hand in.

## What to hand in

All your code and include files are to be handed in.
