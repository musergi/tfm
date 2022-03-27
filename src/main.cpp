#include <iostream>
#include "ArgumentParser.hpp"

int main(int argc, char **argv) {
  ArgumentParser parser;
  parser.addArgument("list");
  parser.parseArgs(argc, argv);
  if (parser.isSet("list")) {
    std::cout << "Entering listing mode" << std::endl;
  }
  return 0;
}
