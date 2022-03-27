#include <iostream>
#include <papi.h>
#include "Event.hpp"

int main(int argc, char **argv) {
  Event event = Event::first();
  std::cout << event << std::endl;
  return 0;
}
