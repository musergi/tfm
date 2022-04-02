#pragma once

#include <string>
#include <ostream>
#include "Context.hpp"

namespace papi {
  class Event {
  private:
    const Context *context;
    int code;

  public:
    Event(const Context *context, int code);
    Event(const Context *context, const char *symbol);

    /* Attribute access methods */
    unsigned int getCode() const;
    std::string getSymbol() const;
    std::string getShortDescription() const;
    std::string getLongDescription() const;
    std::string getUnits() const;
    bool isDerived() const;

    /* Iteration methods */
    static Event first(const Context *context);
    bool hasNext() const;
    Event next() const;
  };
  
  std::ostream &operator<<(std::ostream &os, Event &event);
}
