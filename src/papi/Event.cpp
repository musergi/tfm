#include "Event.hpp"

#include <cstring>
#include <stdexcept>
#include <papi.h>
#include "PapiException.hpp"

namespace papi {
  Event::Event(const Context *context, int code) : context(context), code(code) {
  }

  Event::Event(const Context *context, const char* symbol) : context(context) {
    context->checkError(PAPI_event_name_to_code(symbol, &code));
  }

  unsigned int Event::getCode() const {
    return code;
  }

  static void getEventInfo(const Context *context, int code, PAPI_event_info_t *eventInfo) {
    context->checkError(PAPI_get_event_info(code, eventInfo));
  }

  std::string Event::getSymbol() const {
    PAPI_event_info_t eventInfo;
    getEventInfo(context, code, &eventInfo);
    return eventInfo.symbol;
  }

  std::string Event::getShortDescription() const {
    PAPI_event_info_t eventInfo;
    getEventInfo(context, code, &eventInfo);
    return eventInfo.short_descr;
  }

  std::string Event::getLongDescription() const {
    PAPI_event_info_t eventInfo;
    getEventInfo(context, code, &eventInfo);
    return eventInfo.long_descr;
  }

  std::string Event::getUnits() const {
    PAPI_event_info_t eventInfo;
    getEventInfo(context, code, &eventInfo);
    return eventInfo.units;
  }

  bool Event::isDerived() const {
    PAPI_event_info_t eventInfo;
    getEventInfo(context, code, &eventInfo);
    return strcmp(eventInfo.derived, "NOT_DERIVED") != 0;
  }

  Event Event::first(const Context *context) {
    int eventCode = 0 | PAPI_PRESET_MASK;
    context->checkError(PAPI_enum_event(&eventCode, PAPI_ENUM_FIRST));
    return Event(context, eventCode);
  }

  bool Event::hasNext() const {
    int eventCode = code;
    int error = PAPI_enum_event(&eventCode, PAPI_ENUM_EVENTS);
    return error == PAPI_OK;
  }

  Event Event::next() const {
    int eventCode = code;
    context->checkError(PAPI_enum_event(&eventCode, PAPI_ENUM_EVENTS));
    return Event(context, eventCode);
  }

  std::ostream &operator<<(std::ostream &os, Event &event) {
    return os << "{" << event.getCode() << ", " << event.getSymbol() << "}";
  }
}