#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <papi.h>

void handle_error(int retval) {
  fprintf(stderr, "PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

int main() {
  int eventSet = PAPI_NULL;
  unsigned int native = 0x0;
  int retval, i;
  PAPI_event_info_t info;
  PAPI_event_info_t *infostructs;

  /* Init PAPI library */
  retval = PAPI_library_init(PAPI_VER_CURRENT);

  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI library init error!\n");
    exit(1);
  }

  /* Check to see if the preset, PAPI_TOT_INS, exists */
  retval = PAPI_query_event(PAPI_TOT_INS);
  if (retval != PAPI_OK) {
    fprintf(stderr,"No instruction counter? How lame.\n");
    handle_error(retval);
  }

  /* Get details about the preset, PAPI_TOT_INS */
  retval = PAPI_get_event_info(PAPI_TOT_INS, &info);
  if (retval != PAPI_OK) {
    fprintf(stderr,"No event info? How lame.\n");
    handle_error(retval);
  }

  if (info.count > 0)
    printf ("This event is available on this hardware.\n");

  if (strcmp(info.derived, "NOT_DERIVED"))
    printf ("This event is a derived event on this hardware.\n");

  /* Count the number of available preset events between
     PAPI_TOT_INS and the end of the preset list */
  retval = 0;
  i = PAPI_TOT_INS;

  while (PAPI_enum_event(&i, PAPI_ENUM_EVENTS) == PAPI_OK)
    retval++;
  printf ("There are %d PRESET events after PAPI_TOT_INS.\n", retval);
  exit(0);
}
