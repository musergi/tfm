#include <iostream>
#include <chrono>
#include <thread>
#include "Context.hpp"
#include "Event.hpp"
#include "EventSet.hpp"
#include "DataFrame.hpp"

int main(int argc, char const **argv) {
  papi::Context context;
  context.setDomainAll();
  papi::EventSet eventSet(&context);
  eventSet.setGranularityMax();

  std::vector<std::string> columns;
  columns.push_back("timestamp");
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
  for (int i = 0; i < 100; i++) {
    long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto eventCounts = eventSet.resetRead();
    eventCounts.insert(eventCounts.begin(), timestamp);
    df.add(eventCounts);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  /* Show recording results */
  std::cout << df << std::endl;
  df.toCsv("out.csv");
  return 0;
}
