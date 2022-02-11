#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <papi.h>

void handle_error(int retval) {
  fprintf(stderr, "PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void libInit() {
  int returnValue;
  returnValue = PAPI_library_init(PAPI_VER_CURRENT);
  if (returnValue != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI library init error!\n");
    exit(1);
  }
}

void createEventSet(int *eventSet) {
  if (PAPI_create_eventset(eventSet) != PAPI_OK) {
    fprintf(stderr, "Failed to create event set.\n");
    handle_error(1);
  }
}

void addEvent(int eventSet, int event) {
  int returnValue = PAPI_add_event(eventSet, event); 
  if (returnValue != PAPI_OK) {
    fprintf(stderr, "Failed to add event set.\n");
    handle_error(returnValue);
  }
}

void startEvent(int eventSet) {
  if (PAPI_start(eventSet) != PAPI_OK) {
    fprintf(stderr, "Failed to start event set.\n");
    handle_error(1);
  }
}

void readEvent(int eventSet, long long *values) {
  if (PAPI_read(eventSet, values) != PAPI_OK) {
    handle_error(1);
  }
}

void stopEvent(int eventSet, long long *values) {
  if (PAPI_stop(eventSet, values) != PAPI_OK) {
    fprintf(stderr, "Failed to stop event set.\n");
    handle_error(1);
  }
}

int main() {
  int eventSet = PAPI_NULL;
  long long values[1];
  int i, acc;

  /* Init counter */
  libInit();
  createEventSet(&eventSet);
  addEvent(eventSet, PAPI_TOT_INS);
  startEvent(eventSet);

  /* Do actual work */
  acc = 0;
  for (i = 0; i < 1000; i++) {
    acc += i;
  }
  printf("Test accumulator %d\n", acc);

  /* Measure */
  stopEvent(eventSet, values);
  printf("Value of TOT_INS after work %lld\n", values[0]);

  return 0;
}
