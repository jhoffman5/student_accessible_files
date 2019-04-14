#pragma once
#include <vector>
#include "fw.hpp"

class PalmTree : public Rocket
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};
