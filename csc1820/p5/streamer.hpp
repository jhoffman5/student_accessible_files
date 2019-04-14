#pragma once
#include <vector>
#include "fw.hpp"

class Streamer : public Rocket
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};

class DoubleStreamer : public Streamer
{
  public:
	virtual void Trigger(std::vector<Rocket *> & v);
};
