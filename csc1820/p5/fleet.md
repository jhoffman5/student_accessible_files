# The Fleet class

The ```Fleet``` class manages the details of a collection of ```Rocket```. The relationship between a ```Fleet``` object and ```Rocket``` objects is that a ```Fleet``` **has a** number of ```Rocket``` instances.

## The Fleet include file

This is the contents of my ```fleet.hpp```:

```c++
#pragma once
#include <vector>
#include <ncurses.h>
#include "fw.hpp"
#include "streamer.hpp"
#include "palmtree.hpp"


class Fleet {
public:
	/*	Cull() is responsible for removing Rockets whose age has risen to
		the age limit specified in the Factory method.
	*/
	void Cull();
	
	/*	Birth() is responsible for spawning new Rockets. The implementation
		details are all hidden within Birth(). Birth() calls the Factory 
		method which does the actual birthing.

		Rockets are dynamically allocated. Therefore must be freeed when culled.
	*/
	void Birth(float initial_up_force);

	/*	Step() advances the simulation for the entire Fleet. Each Rocket's own
		Step() function is called in turn. It is in the Rocket's Step() function that the physics are progressed, age increased and perhaps the Rocket will Trigger() causing an explosion of subrockets to be made.
	*/
	void Step();

	/*	Draw() causes each Rocket Draw() method to be called.
	*/
	void Draw();

private:
	/*	This may be your first Design Pattern. It implements the Factory pattern.
		https://www.geeksforgeeks.org/design-patterns-set-2-factory-method/

		A Factory method is a good choice here because one of a number of Rocket
		subclasses are to be made. The Factory hides how the choice of subclass is
		made and also how the newly made instances are initialized.
	*/
	Rocket * RocketFactory(float initial_up_force);

	/*	This is the collection of Rockets belonging to the Fleet. These are pointers
		to Rockets which can actually be one of several subclasses. Because they are
		all subclasses of Rocket, they can live on the same vector and be called / used
		in the same way.
	*/
	std::vector<Rocket *> rockets;
};

```

## RocketFactory()

This may be your first Design Pattern. It implements the Factory pattern.

https://www.geeksforgeeks.org/design-patterns-set-2-factory-method/

A Factory method is a good choice here because one of a number of Rocket
subclasses are to be made. The Factory hides how the choice of subclass is
made and also how the newly made instances are initialized.

Within ```RocketFactory``` dynamically allocate a subclass of Rocket. Choose which
subclass at random. There are three subclasses defined in this project which are
intended to be launched from ground level. The fourth ```Sparkler``` is used for
subrockets. You can, for example, allocate one of the three chosen with 1/3 probability.

Notice that ```RocketFactory``` returns a pointer to a Rocket. This is so that all types
of Rockets can be built by the factory. It is not the job of ```RocketFactory``` to add the new rocket to the collection of rockets. That is the job of ```Birth```.

In addition to choosing which subclass to create, this method is also responsible for calling:

- SetTriggerAge()
- SetAgeLimit()
- SetPosition()
- SetForce()

## More about Step()

The ```Fleet::Step()``` iterates over the existing ```rockets```. The ```Step``` method in each rocket could cause more sub rockets to be created. This is a problem for your iterating. Suppose there are three existing rockets, A, B and C. When B's ```Step()``` is called, it adds two more rockets to the ```Fleet``` collection, say D and E. Now the ```rockets``` vector has A, B, C, D and E. But you don't want to iterate over the newly added rockets.

The solution I've designed is to declare a temporary second vector of rockets local to the ```Fleet::Step()```. Each rocket's own ```Step``` adds to the local vector.

Once all new sub rockets are accumulated in the local vector (in other words, you're done iterating), add the entire local vector to the class's vector.

Since there might be many new sub rockets in the local vector, you might wonder how to add many new elements to a vector all at once rather than one at a time.

If ```v``` is the name of your local vector of ```Rocket```, then you can add all of ```v``` to ```rockets``` like this:

```c++
rockets.insert(rockets.end(), v.begin(), v.end());
```

The first argument indicates where to insert the new elements. The next two arguments must come from the same collection (as each other) and indicate the range of elements in the other collection to be added.
