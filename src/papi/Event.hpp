#pragma once

#include <string>

class Event {
  unsigned int code;
public:
  Event(unsigned int code);
  std::string getSymbol();
};
