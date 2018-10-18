/*	Project:    NAME OF PROJECT GOES HERE
	Name:       YOUR NAME GOES HERE
    Partner:    PARTNER'S NAME IF ANY
    Class:      example: CSC 1810 - Section 1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum ContainerType
{
	Can,
	Bottle,
	Carton
};

struct Beverage
{
	Beverage(float size, ContainerType ct, string k)
	{
		cout << "Beverage constructor" << endl;
		size_in_ounces = size;
		container = ct;
		kind = k;
	}

	// structs default to public
	string kind;
	ContainerType container;

	float SizeInLiters();
	float SizeInOunces();
	void RunUnitTests();

  private:
	float size_in_ounces;
};

float Beverage::SizeInOunces()
{
	return size_in_ounces;
}

float Beverage::SizeInLiters()
{
	return size_in_ounces * 0.0295735;
}

/*
struct BoxOfBeverages
{
	BoxOfBeverages(int number_of_beverages);
	vector<Beverage> b;
};

BoxOfBeverages::BoxOfBeverages(int number_of_beverages)
{
	cout << "BoxOfBeverages constructor" << endl;
	b.resize(number_of_beverages);
}
*/

int main(int argc, char *argsv[])
{
	vector<ContainerType> ctypes = {Can, Bottle, Carton};
	for (unsigned int i = 0; i < ctypes.size(); i++)
	{
		Beverage b(12, ctypes.at(i), "Fanta");
		if (b.container == ctypes.at(i))
		{
			cout << "Container member test: PASSED" << endl;
		}
		else
		{
			cout << "Container member test: FAILED" << endl;
		}
	}

	// This causes the program to pause at its completion.
	{
		char c;
		cout << "Hit enter to exit:";
		cin.get(c);
	}
	return 0;
}