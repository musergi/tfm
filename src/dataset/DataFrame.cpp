#include "DataFrame.hpp"

#include <stdexcept>

namespace data {
  DataFrame::DataFrame(std::vector<std::string> columns) : columns(columns) {
  }

  DataFrame::DataFrame(char const **columns, unsigned int count) : columns(count) {
    for (int i = 0; i < count; i++) {
      this->columns[i] = std::string(columns[i]);
    }
  }
  
  unsigned int DataFrame::size() const {
    return content.size() / columns.size();
  }

  void DataFrame::add(std::vector<long long> const &series) {
    if (series.size() != columns.size()) {
      throw std::invalid_argument("Size of series did not match columns");
    }
    for (long long dataPoint : series) {
      content.push_back(dataPoint);
    }
  }

  std::ostream &operator<<(std::ostream &os, DataFrame &df) {
    std::vector<int> columnWidths(df.columns.size());
    for (int i = 0; i < df.columns.size(); i++) {
      columnWidths[i] = df.columns[i].size();
      for (int j = 0; j < df.size(); j++) {
        int size = std::to_string(df.content.at(j * df.columns.size() + i)).size();
        if (size >= columnWidths[i]) {
          columnWidths[i] = size;
        }
      }
    }

    for (int titleIdx = 0; titleIdx < df.columns.size(); titleIdx++) {
      std::string title = df.columns[titleIdx];
      int width = columnWidths[titleIdx];
      if (titleIdx != 0) {
        os << "  ";
      }
      for (int i = 0; i < width - title.size(); i++) {
        os << " ";
      }
      os << title;
    }
    os << "\n";

    for (int rowIdx = 0; rowIdx < df.size(); rowIdx++) {
      for (int columnIdx = 0; columnIdx < df.columns.size(); columnIdx++) {
        auto const& valueString = std::to_string(df.content.at(rowIdx * df.columns.size() + columnIdx));
        if (columnIdx != 0) {
          os << "  ";
        }
        for (int i = 0; i < columnWidths[columnIdx] - valueString.size(); i++) {
          os << " ";
        }
        os << valueString;
      }
      os << "\n";
    }
    return os;
  }
}
