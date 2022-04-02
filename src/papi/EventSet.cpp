#include "EventSet.hpp"

#include "PapiException.hpp"

EventSet::EventSet() : eventSet(PAPI_NULL), eventCount(0) {
    int error = PAPI_create_eventset(&eventSet);
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
}

EventSet::~EventSet() {
    int error = PAPI_cleanup_eventset(&eventSet);
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
    error = PAPI_destroy_eventset(&eventSet);
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
}

void EventSet::addEvent(Event event) {
    int error = PAPI_add_event(&eventSet, event.getCode());
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
    eventCount++;
}

void EventSet::start() {
    int error = PAPI_start(eventSet);
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
}

void EventSet::stop() {
    long_long *values = new long_long[eventCount];
    int error = PAPI_stop(eventSet, values);
    if (error != PAPI_OK) {
        throw PapiException(error);
    }
    delete[] values;
}