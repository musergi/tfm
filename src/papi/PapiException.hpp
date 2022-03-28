#pragma once

#include <stdexcept>

class PapiException : public std::runtime_error {
public:
  PapiException(int error);
private:
  static std::string getPapiError(int error);
};