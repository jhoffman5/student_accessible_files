#pragma once
#include <limits>
#include <vector>
#include <fstream>

/*	frand() is defined in main.cpp.
*/

float frand();

class Rocket
{
  public:
	Rocket();
	virtual ~Rocket();

	void SetTriggerAge(int i);
	void SetAgeLimit(int i);
	void SetPosition(Rocket &other);
	void SetPosition(float x, float y);
	void SetForce(float x, float y);
	virtual void Draw();
	virtual void Step(std::vector<Rocket *> & v);
	virtual void Trigger(std::vector<Rocket *> & v);

	int GetAge();
	bool IsAlive();
	bool IsTriggered();

	static void SetGravity(float g);

  protected:
	int age;
	int age_limit;
	int trigger_age;

	struct
	{
		float x, y;
	} position;

	struct
	{
		float x, y;
	} force;

	static float gravity;
};
