#pragma once

#include <string>
#include <ostream>
#include <papi.h>

class Event {
private:
  int code;

public:
  Event(int code);
  Event(const char *symbol);

  /* Attribute access methods */
  unsigned int getCode();
  std::string getSymbol();
  std::string getShortDescription();
  std::string getLongDescription();
  std::string getUnits();
  bool isDerived();

  /* Iteration methods */
  static Event first();
  bool hasNext();
  Event next();

private:
  void getEventInfo(PAPI_event_info_t *eventInfo);
};

std::ostream &operator<<(std::ostream &os, Event &event);
