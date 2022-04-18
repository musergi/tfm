#include "Context.hpp"

#include <stdexcept>
#include <papi.h>
#include "PapiException.hpp"

namespace papi {
  Context::Context() {
      int actualVersion = PAPI_library_init(PAPI_VER_CURRENT);
      if (actualVersion != PAPI_VER_CURRENT && actualVersion > 0) {
          throw std::runtime_error("Loaded wrong version of PAPI");
      }
      if (actualVersion < 0) {
          throw std::runtime_error("Could not load PAPI");
      }
  }

  Context::~Context() {
  }

  void Context::checkError(int error) const {
      if (error != PAPI_OK) {
          throw PapiException(error);
      }
  }

  void Context::setDomainUser() {
    checkError( PAPI_set_domain(PAPI_DOM_USER) );
  }

  void Context::setDomainKernel() {
    checkError( PAPI_set_domain(PAPI_DOM_KERNEL) );
  }


  void Context::setDomainAll() {
    checkError( PAPI_set_domain(PAPI_DOM_ALL) );
  }
}
