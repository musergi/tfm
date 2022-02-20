#include <iostream>
#include <papi.h>
#include "Event.hpp"

int main() {
  Event event = Event::first(PAPI_UE_MASK);
  std::cout << event << std::endl;
  return 0;
}
