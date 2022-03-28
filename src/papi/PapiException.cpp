#include "PapiException.hpp"

#include <sstream>
#include <papi.h>

PapiException::PapiException(int error) : std::runtime_error(PapiException::getPapiError(error)) {
}

std::string PapiException::getPapiError(int code) {
    std::ostringstream message;
    message << "PAPI error:";
    message << code;
    message << ":";
    message << PAPI_strerror(code);
    return message.str();
}