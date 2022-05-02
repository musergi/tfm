#pragma once

#include <vector>
#include <string>
#include <ostream>

namespace data {
  class DataFrame {
    private:
      std::vector<std::string> columns;
      std::vector<long long> content;
    public:
      DataFrame(std::vector<std::string> columns);
      DataFrame(char const **columns, unsigned int count);
      unsigned int size() const;
      void add(std::vector<long long> const &series);
      friend std::ostream &operator<<(std::ostream &os, Event &DataFrame);
  };

  std::ostream &operator<<(std::ostream &os, Event &DataFrame);
}
