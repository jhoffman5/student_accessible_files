# Required specializations (derived classes)

When you need to extend or alter the characteristics of a class, you can derive a subclass from it. Notice in each of the subclasses below, only one or two methods are mentioned. What that is saying is: *all the other features of the base class were fine - these are the only ones you want to change.*

## Sparkler

```c++
class Sparkler : public Rocket
{
  public:
	void Draw();
};
```

The ```Sparkler::Draw()``` alternates the rendering of the rocket between '+' and 'x' based on age where the base class simply uses '*' all the time.

## Palm tree

```c++
class PalmTree : public Rocket
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};
```

A Palm Tree rocket spawns 8 ```Sparklers``` in a horizontal arrangement when triggered.
A force of left or right and up a little should be added to the force of the original particle to make the initial force of the ```Sparklers```. The initial position of each ```Sparkler``` is the position of the original particle.

## Streamer

```c++
class Streamer : public Rocket
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};
```

The ```Streamer``` spawns 8 ```Sparklers``` in a circular pattern. The square root of two is your friend. Why? ```Trigger()``` causes the spawning to take place.

## DoubleStreamer

```c++
class DoubleStreamer : public Streamer
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};
```

The ```DoubleStreamer``` inherits from ```Streamer```. It differs only in how many ```Sparklers``` are spawned (and with what force). The ```DoubleStreamer``` spawns eight more ```Sparklers``` than ```Streamer``` in the same directions but with half as much force. 

**There is a special requirement in DoubleStreamer:**

The ```DoubleStreamer``` ```Trigger()``` **must not** duplicate the work of the ```Trigger()``` in ```Streamer```. Instead, it must leverage the work that can be done by its *superclass*.
