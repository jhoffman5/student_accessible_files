# The main program

Following is a complete and working (for me) ```main.cpp```.

```c++
#include <thread>
#include <chrono>
#include <vector>
#include <ctime>
#include <ncurses.h>

#include "fw.hpp"
#include "streamer.hpp"
#include "palmtree.hpp"
#include "fleet.hpp"

using namespace std;

/*	frand() - this function returns a floating point value chosen
	at random in the range of -0.5 to 0.5. It can be used to perturb
	constant values.

	For example, if you want values near 4 you can do this:
	4 + frand()

	This will return in values from 3.5 to 4.5.
*/

float frand()
{
	return float(rand()) / float(RAND_MAX) - 0.5f;
}

/*	main()

	The program currently offers no means of termination other than CNTRL-c.
*/

int main(int argc, char *argv[])
{
	float initial_up_force = 4.0;
	srand((unsigned int)time(nullptr));
	Fleet fleet;

	/*	If argv[1] is given, it is taken to be a value for the initial
		up force given to a rocket. The default up force is 4 in this
		program. If your terminal window is short, use a smaller number.
		If your terminal window is very tall, try a larger number.
	*/
	if (argc > 1) {
		initial_up_force = stof(argv[1]);
	}

	initscr();
	curs_set(0);
	/*	Gravity is the pervasive down force and is constant for all
		rockets. Because it is the same for all rockets, it is declared
		as a static. Rocket::SetGravity() is likewise a static method
		within Rocket.
	*/
	Rocket::SetGravity(-0.2);

	/*	A Fleet object manages (and hides the details of) the collection
		of Rockets. The flow here is:
		- Possibly make new rockets
		- Advance the simulation for each currently defined rocket. Note
		  that if the given rocket is one which explodes creating subrockets,
		  it is done within the Step() function.
		- Draw each rocket.
		- Eliminate rockets that have aged out.
	*/
	while (true)
	{
		erase();
		fleet.Birth(initial_up_force);
		fleet.Step();
		fleet.Draw();
		fleet.Cull();
		box(stdscr, 0, 0);
		mvaddstr(0, 1, " RETRO FIREWORKS ");
		refresh();
		this_thread::sleep_for(chrono::milliseconds(40));
	}
	curs_set(1);
	endwin();
	return 0;
}
```
