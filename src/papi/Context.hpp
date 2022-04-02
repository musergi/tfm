#pragma once

namespace papi {
  class Context {
  public:
    Context();
    ~Context();
    void checkError(int error) const;
  };
}