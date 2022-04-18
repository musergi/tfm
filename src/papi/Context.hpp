#pragma once

namespace papi {
  class Context {
  public:
    Context();
    ~Context();
    void checkError(int error) const;
    void setDomainUser();
    void setDomainKernel();
    void setDomainAll();
  };
}
