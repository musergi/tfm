#ifndef EVENT_LIST_H
#define EVENT_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <papi.h>

typedef struct {
  unsigned int eventCode;
  char symbol[PAPI_HUGE_STR_LEN];
  char shortDescription[PAPI_MIN_STR_LEN];
  char longDescription[PAPI_HUGE_STR_LEN];
  char units[PAPI_MIN_STR_LEN];
  bool isDerived;
} EventInfo;

typedef struct {
  unsigned int count;
  EventInfo *events;
} EventList;

void eventListAvailable(EventList *eventList);

#endif
