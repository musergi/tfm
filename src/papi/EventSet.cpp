#include "EventSet.hpp"

#include <papi.h>
#include "PapiException.hpp"

namespace papi {
  EventSet::EventSet(const Context *context) : eventSet(PAPI_NULL), eventCount(0), context(context) {
    context->checkError(PAPI_create_eventset(&eventSet));
  }

  EventSet::~EventSet() {
    context->checkError(PAPI_cleanup_eventset(eventSet));
    context->checkError(PAPI_destroy_eventset(&eventSet));
  }

  void EventSet::addEvent(Event event) {
    context->checkError(PAPI_add_event(eventSet, event.getCode()));
    eventCount++;
  }

  void EventSet::start() {
    context->checkError(PAPI_start(eventSet));
  }

  std::vector<long long> EventSet::stop() {
    std::vector<long long> values(eventCount * sizeof(long long));
    context->checkError(PAPI_stop(eventSet, values.data));
    return values;
  }
}