#include "EventSet.hpp"

#include "PapiException.hpp"

namespace papi {
  EventSet::EventSet(const Context *context) : eventSet(PAPI_NULL), eventCount(0), context(context) {
    context->checkError(PAPI_create_eventset(&eventSet));
  }

  EventSet::~EventSet() {
    context->checkError(PAPI_cleanup_eventset(&eventSet));
    context->checkError(PAPI_destroy_eventset(&eventSet));
  }

  void EventSet::addEvent(Event event) {
    context->checkError(PAPI_add_event(&eventSet, event.getCode()));
    eventCount++;
  }

  void EventSet::start() {
    context->checkError(PAPI_start(eventSet));
  }

  void EventSet::stop() {
    long_long *values = new long_long[eventCount];
    context->checkError(PAPI_stop(eventSet, values));
    delete[] values;
  }
}