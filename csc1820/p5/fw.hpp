#pragma once
#include <limits>
#include <vector>
#include <fstream>

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
	virtual void Step();
	virtual void Trigger();

	int GetAge();
	bool IsAlive();
	bool IsTriggered();

	static void SetGravity(float g);
	static void SetLogFile(std::ofstream *log_file);
	static void SetVector(std::vector<Rocket *> *);

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
	static std::ofstream *log_file;
	static std::vector<Rocket *> *rockets;
};
