#include "dataframe.hpp"

#include <stdexcept>

namespace data {
  DataFrame::DataFrame(std::vector<std::string> columns) : columns(columns) {
  }

  DataFrame::DataFrame(char const **columns, unsigned int count) : columns(count) {
    for (int i = 0; i < count; i++) {
      this.columns[i] = std::string(columns[i]);
    }
  }
  
  unsigned int size() const {
    return data.size() / columns.size();
  }

  void add(std::vector<long long> const &series) {
    if (series.size() != columns.size()) {
      throw std::invalid_argument("Size of series did not match columns");
    }
    for (long long dataPoint : series) {
      data.push_back(dataPoint);
    }
  }
}
