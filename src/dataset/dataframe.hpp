#pragma once

#include <vector>
#include <string>

namespace data {
  class DataFrame {
    private:
      std::vector<std::string> columns;
      std::vector<long long> data;
    public:
      DataFrame(std::vector<std::string> columns);
      DataFrame(char const **columns, unsigned int count);
      unsigned int size() const;
      void add(std::vector<long long> const &series);
  };
}
