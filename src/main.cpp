#include <iostream>
#include "ArgumentParser.hpp"
#include "Event.hpp"

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
    for (std::string eventSymbol: parser.getValues("record")) {
      papi::Event event(&context, eventSymbol.c_str());
      std::cout << "Recording: " << event.getCode() << ", " << event.getSymbol() << std::endl;
    }
  }
  return 0;
}
