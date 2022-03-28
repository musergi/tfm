#include "PapiException.hpp"

#include <string>
#include <papi.h>

PapiException::PapiException(int error) : std::runtime_error(PapiException::getPapiError(error)) {
}

std::string PapiException::getPapiError(int code) {
    std::string message("PAPI error:");
    message += std::to_string(code);
    message += ":";
    message += PAPI_strerror(code);
    return message;
}