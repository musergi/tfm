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
    void setGranularityThread();
    void setGranularityProcess();
    void setGranularityCPU();
    void setGranularityCPUs();
  };
}
