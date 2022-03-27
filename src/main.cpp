#include <iostream>
#include "ArgumentParser.hpp"
#include "Event.hpp"

int main(int argc, const char **argv) {
  ArgumentParser parser;
  parser.addArgument("list");
  parser.parseArgs(argc, argv);
  if (parser.isSet("list")) {
    std::cout << "Entering listing mode." << std::endl;
    Event event = Event::first();
    std::cout << event.getSymbol();
    while (event.hasNext()) {
      event = event.next();
      std::cout << "," << event.getSymbol();
    }
    std::cout << std::endl;
  }
  return 0;
}
