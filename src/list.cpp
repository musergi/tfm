#include <iostream>
#include "Context.hpp"
#include "Event.hpp"

int main(int argc, const char **argv) {
  papi::Context context;
  auto event = papi::Event::first(&context);
  std::cout << event.getSymbol();
  while (event.hasNext()) {
    event = event.next();
    std::cout << "\n" << event.getSymbol();
  }
  std::cout << std::endl;
  return 0;
}
