#include "Event.hpp"

#include <cstring>
#include <stdexcept>

Event::Event(unsigned int code) : code(code) {
}

std::string Event::getSymbol() {
  PAPI_event_info_t eventInfo;
  getEventInfo(&eventInfo);
  return eventInfo.symbol;
}

std::string Event::getShortDescription() {
  PAPI_event_info_t eventInfo;
  getEventInfo(&eventInfo);
  return eventInfo.short_descr;
}

std::string Event::getLongDescription() {
  PAPI_event_info_t eventInfo;
  getEventInfo(&eventInfo);
  return eventInfo.long_descr;
}

std::string Event::getUnits() {
  PAPI_event_info_t eventInfo;
  getEventInfo(&eventInfo);
  return eventInfo.units;
}

bool Event::isDerived() {
  PAPI_event_info_t eventInfo;
  getEventInfo(&eventInfo);
  return strcmp(eventInfo.derived, "NOT_DERIVED") != 0;
}

void Event::getEventInfo(PAPI_event_info_t *eventInfo) {
  int error = PAPI_get_event_info(code, eventInfo);
  if (error != PAPI_OK) {
    throw std::logic_error("Failed to fetch event info");
  }
}
