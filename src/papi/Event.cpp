#include "Event.hpp"

#include <cstring>
#include <stdexcept>
#include <papi.h>
#include "PapiException.hpp"

Event::Event(int code) : code(code) {
}

Event::Event(const char* symbol) {
  int error = PAPI_event_name_to_code(symbol, &code);
  if (error != PAPI_OK) {
      throw PapiException(error);
  }
}

unsigned int Event::getCode() {
  return code;
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

Event Event::first() {
  int eventCode = 0 | PAPI_PRESET_MASK;
  int error = PAPI_enum_event(&eventCode, PAPI_ENUM_FIRST);
  if (error) {
    throw std::out_of_range("Failed to fetch first event");
  }
  return Event(eventCode);
}

bool Event::hasNext() {
  int eventCode = code;
  int error = PAPI_enum_event(&eventCode, PAPI_ENUM_EVENTS);
  return error == PAPI_OK;
}

Event Event::next() {
  int eventCode = code;
  int error = PAPI_enum_event(&eventCode, PAPI_ENUM_EVENTS);
  if (error) {
    throw std::out_of_range("Failed to fetch next event");
  }
  return Event(eventCode);
}

void Event::getEventInfo(PAPI_event_info_t *eventInfo) {
  int error = PAPI_get_event_info(code, eventInfo);
  if (error != PAPI_OK) {
    throw std::logic_error("Failed to fetch event info");
  }
}


std::ostream &operator<<(std::ostream &os, Event &event) {
  return os << "{" << event.getCode() << ", " << event.getSymbol() << "}";
}
