#include "EventSet.hpp"

#include <iostream>
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

  void EventSet::setGranularityThread() {
    setGranularity(PAPI_GRN_THR);
  }

  void EventSet::setGranularityProcess() {
    setGranularity(PAPI_GRN_PROC);
  }
  
  void EventSet::setGranularityCPU() {
    setGranularity(PAPI_GRN_SYS);
  }

  void EventSet::setGranularityCPUs() {
    try {
      setGranularity(PAPI_GRN_SYS_CPU);
    } catch (PapiException& e) {
      std::cerr << "Unable to set granularity SYS_CPU" << std::endl;
      setGranularityCPU();
    }
  }

  void EventSet::start() {
    context->checkError(PAPI_start(eventSet));
  }

  std::vector<long long> EventSet::resetRead() {
    std::vector<long long> values(eventCount);
    context->checkError( PAPI_accum(eventSet, values.data()) );
    return values;
  }

  std::vector<long long> EventSet::stop() {
    std::vector<long long> values(eventCount);
    context->checkError(PAPI_stop(eventSet, values.data()));
    return values;
  }

  void EventSet::setGranularity(int granularity) {
    context->checkError( PAPI_assign_eventset_component(eventSet, 0) );
    PAPI_granularity_option_t granularityOption;
    granularityOption.def_cidx = 0;
    granularityOption.eventset = eventSet;
    granularityOption.granularity = granularity;
    context->checkError( PAPI_set_opt(PAPI_GRANUL, (PAPI_option_t *)&granularityOption) );
  }
}
