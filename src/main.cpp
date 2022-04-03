#include <iostream>
#include "ArgumentParser.hpp"
#include "Context.hpp"
#include "Event.hpp"
#include "EventSet.hpp"

int main(int argc, const char **argv) {
  ArgumentParser parser;
  parser.addArgument("list");
  parser.addArgument("record");
  parser.parseArgs(argc, argv);

  if (parser.isSet("list")) {
    std::cout << "Entering listing mode." << std::endl;
    papi::Context context;
    papi::Event event = papi::Event::first(&context);
    std::cout << event.getSymbol();
    while (event.hasNext()) {
      event = event.next();
      std::cout << "," << event.getSymbol();
    }
    std::cout << std::endl;
  } else if (parser.isSet("record")) {
    std::cout << "Entering record mode." << std::endl;
    papi::Context context;
    papi::EventSet eventSet(&context);

    /* Get all requested events */
    for (std::string eventSymbol: parser.getValues("record")) {
      papi::Event event(&context, eventSymbol.c_str());
      eventSet.addEvent(event);
      std::cout << "Recording: " << event.getCode() << ", " << event.getSymbol() << std::endl;
    }

    /* Start recording */
    eventSet.start();

    /* Run program */
    int acc = 0;
    for (int i = 0; i < 10000; i++) {
      acc++;
    }
    std::cout << acc << std::endl;

    /* Show recording results */
    std::vector<long long> counts = eventSet.stop();
    for (int i = 0; i < counts.size(); i++) {
      std::cout << parser.getValues("record")[i];
      std::cout << counts[i] << std::endl;
    }
  } else {
    std::cout << "One of the parameters list or record must be selected" << std::endl;
  }
  return 0;
}
