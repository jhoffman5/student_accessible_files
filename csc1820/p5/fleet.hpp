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
		Step() function is called in turn. It is in the Rocket's Step() function
		that the physics are progressed, age increased and perhaps the Rocket
		will Trigger() causing an explosion of subrockets to be made.
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

