#include <iostream>
#include <chrono>
#include <thread>
#include "Context.hpp"
#include "Event.hpp"
#include "EventSet.hpp"

int main(int argc, char const **argv) {
  papi::Context context;
  context.setDomainAll();
  papi::EventSet eventSet(&context);
  eventSet.setGranularityMax();

  for (int i = 1; i < argc; i++) {
    papi::Event event(&context, argv[i]);
    eventSet.addEvent(event);
    std::cout << "Recording: " << event.getCode() << ", " << event.getSymbol() << std::endl;
  }

  /* Start recording */
  eventSet.start();

  /* Run program */
  std::vector<std::vector<long long>> measures;
  for (int i = 0; i < 100; i++) {
    measures.push_back(eventSet.resetRead());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  /* Show recording results */
  for (int i = 0; i < measures[0].size(); i++) {
    std::cout << argv[i + 1] << ": ";
    for (int j = 0; j < measures.size(); j++) {
      if (j != 0) {
        std::cout << ",";
      }
      std::cout << measures[j][i];
    }
    std::cout << std::endl;
  }
  return 0;
}
