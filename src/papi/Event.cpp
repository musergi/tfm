#include "Event.hpp"

#include <stdexcept>
#include <papi.h>

Event::Event(unsigned int code) : code(code) {
}

std::string Event::getSymbol() {
  PAPI_event_info_t eventInfo;
  int error = PAPI_get_event_info(event_code, &eventInfo);
  if (error != PAPI_OK) {
    throw std::logic_error("Failed to fetch event info");
  }
  return eventInfo.symbol;
}
