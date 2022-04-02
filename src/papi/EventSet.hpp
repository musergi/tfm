#pragma once

#include <papi.h>
#include "Event.hpp"

class EventSet {
private:
  int eventSet;
  int eventCount;
public:
  EventSet();
  ~EventSet();
  void addEvent(Event event);
  void start();
  void stop()
};