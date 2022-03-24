#include <iostream>
#include <papi.h>
#include "Event.hpp"

int main() {
  Event event = Event::first();
  std::cout << event << std::endl;
  return 0;
}
