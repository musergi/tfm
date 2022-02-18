#include <unistd.h>
#include "EventSet.h"

int main() {
  long long values[1];
  EventSet events;
  eventSetInit(&events);
  eventSetGranularity(&events, PAPI_GRN_SYS);
  eventSetAddEvent(&events, "PAPI_TOT_INS");
  eventSetStart(&events);
  sleep(2);
  eventSetStop(&events, values);
  printf("System wide PAPI_TOT_INS: %lld\n", values[0]);
  return 0;
}
