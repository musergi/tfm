#include "EventList.h"

static void eventListInit(EventList *eventList);
static unsigned int getEventCount();
static unsigned int getMaskedEventCount(unsigned int mask);
static bool eventGetFirst(EventInfo *info, unsigned int mask);
static void parseEvent(unsigned int eventCode, EventInfo *info);

void eventListAvailable(EventList *eventList) {
  int i = 0;
  eventListInit(eventList);
  if (eventList->count == 0)
    return;
  eventGetFirst(&eventList->events[0])
}

void eventListInit(EventList *eventList) {
  unsigned int eventList->count = getEventCount();
  eventList->events = (EventList *)malloc(eventList->count * sizeof(EventInfo));
}

static unsigned int getEventCount() {
  return getMaskedEventCount(PAPI_PRESET_MASK) + getMaskedEventCount(PAPI_UE_MASK);
}

static unsigned int getMaskedEventCount(unsigned int mask) {
  unsigned int counter;
  unsigned int eventCode = 0 | mask;
  int error = PAPI_enum_event(&eventCode, PAPI_ENUM_FIRST);
  if (error != PAPI_OK) {
    return 0;
  }
  counter = 1;
  while (PAPI_enum_event(&eventCode, PAPI_ENUM_EVENTS) == PAPI_OK) counter++;
  return counter;
}

static void eventGetFirst(EventInfo *info, unsigned int mask) {
  int eventCode = 0 | mask;
  int error = PAPI_enum_event(&eventCode, PAPI_ENUM_FIRST);
  if (error != PAPI_OK) {
    return false;
  }
  parseEvent(eventCode, info);
}

static void parseEvent(unsigned int eventCode, EventInfo *info) {
  PAPI_event_info_t eventInfo;
  int error = PAPI_get_event_info(eventCode, eventInfo);
  /* TODO: Handle error */
  info->eventCode = eventCode;
  strcpy(info->shortDescription, eventInfo->short_descr);
  strcpy(info->longDescription, eventInfo->long_descr);
}
