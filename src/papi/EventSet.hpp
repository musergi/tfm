#pragma once

#include "Context.hpp"
#include "Event.hpp"

namespace papi {
  class EventSet {
  private:
    const Context *context;
    int eventSet;
    int eventCount;
  public:
    EventSet(const Context *context);
    ~EventSet();
    void addEvent(Event event);
    void start();
    void stop();
  };
}