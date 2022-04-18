#include <iostream>
#include <unistd.h>
#include "Context.hpp"
#include "Event.hpp"
#include "EventSet.hpp"

int main(int argc, char const **argv) {
  papi::Context context;
  context.setDomainAll();
  papi::EventSet eventSet(&context);
  context.setGranularityCPUs();

  for (int i = 1; i < argc; i++) {
    papi::Event event(&context, argv[i]);
    eventSet.addEvent(event);
    std::cout << "Recording: " << event.getCode() << ", " << event.getSymbol() << std::endl;
  }

  /* Start recording */
  eventSet.start();

  /* Run program */
  sleep(1);

  /* Show recording results */
  std::vector<long long> counts = eventSet.stop();
  for (int i = 0; i < counts.size(); i++) {
    std::cout << parser.getValues("record")[i];
    std::cout << counts[i] << std::endl;
  }
  return 0;
}
