#include <iostream>
#include <chrono>
#include <thread>
#include "Context.hpp"
#include "Event.hpp"
#include "EventSet.hpp"
#include "Dataframe.hpp"

int main(int argc, char const **argv) {
  papi::Context context;
  context.setDomainAll();
  papi::EventSet eventSet(&context);
  eventSet.setGranularityMax();

  std::vector<std::string> columns;
  for (int i = 1; i < argc; i++) {
    columns.push_back(argv[i]);
    papi::Event event(&context, argv[i]);
    eventSet.addEvent(event);
    std::cout << "Recording: " << event.getCode() << ", " << event.getSymbol() << std::endl;
  }

  /* Start recording */
  data::DataFrame df(columns);
  eventSet.start();

  /* Run program */
  std::vector<std::vector<long long>> measures;
  for (int i = 0; i < 100; i++) {
    df.add(eventSet.resetRead());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  /* Show recording results */
  std::cout << df << std::endl;
  return 0;
}
