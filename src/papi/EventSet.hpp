#pragma once

#include <vector>
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
    void setGranularityThread();
    void setGranularityProcess();
    void setGranularityCPU();
    void setGranularityCPUs();
    void addEvent(Event event);
    void start();
    std::vector<long long> resetRead();
    std::vector<long long> stop();
  private:
    void setGranularity(int granularity);
  };
}