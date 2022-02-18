#ifndef EVENT_SET_H
#define EVENT_SET_H

#include "papi.h"

typedef struct {
	int id;
} EventSet;

void eventSetInit(EventSet *eventSet);
void eventSetGranularity(EventSet *eventSet, int granularity);
void eventSetAddEvent(EventSet *eventSet, const char *name);
void eventSetStart(EventSet *eventSet);
void eventSetStop(EventSet *eventSet, long long *values);

#endif