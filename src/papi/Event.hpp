#pragma once

#include <string>
#include <papi.h>

class Event {
private:
  unsigned int code;
public:
  Event(unsigned int code);
  std::string getSymbol();
  std::string getShortDescription();
  std::string getLongDescription();
  std::string getUnits();
  bool isDerived();
private:
  void getEventInfo(PAPI_event_info_t *eventInfo);
};
