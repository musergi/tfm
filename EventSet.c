#include "EventSet.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void initLibrary();
static void handleError(const char *message, int error);

static bool libraryInit = false;

void eventSetInit(EventSet *eventSet) {
  int error;
  if (!libraryInit) {
    initLibrary();
    libraryInit = true;
  }
  eventSet->id = PAPI_NULL;
  error = PAPI_create_eventset(&eventSet->id);
  if (error != PAPI_OK) {
    handleError("Error event set init", error);
  }
}

static void initLibrary() {
  int returnValue = PAPI_library_init(PAPI_VER_CURRENT);
  if (returnValue != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI library init error\n");
    exit(1);
  }
}

static void handleError(const char *message, int error) {
  fprintf(stderr, "%s\n", message);
  fprintf(stderr, "PAPI error %d: %s\n", error, PAPI_strerror(error));
  exit(1);
}

void eventSetGranularity(EventSet *eventSet, int granularity) {
  int error;
  PAPI_granularity_option_t granularityOption;
  PAPI_assign_eventset_component(eventSet->id, 0);
  granularityOption.def_cidx = 0;
  granularityOption.eventset = eventSet->id;
  granularityOption.granularity = granularity;
  error = PAPI_set_opt(PAPI_GRANUL, (PAPI_option_t *)&granularityOption);
  if (error != PAPI_OK) {
    handleError("Could not set granularity", error);
  }
}

void eventSetAddEvent(EventSet *eventSet, const char *name) {
  int error = PAPI_add_named_event(eventSet->id, name);
  if (error != PAPI_OK) {
    handleError("Could not add event", error);
  }
}

void eventSetStart(EventSet *eventSet) {
  int error = PAPI_start(eventSet->id);
  if (error != PAPI_OK) {
    handleError("Could not start event", error);
  }
}

void eventSetStop(EventSet *eventSet, long long *values) {
  int error = PAPI_stop(eventSet->id, values);
  if (error != PAPI_OK) {
    handleError("Could not stop event", error);
  }
}