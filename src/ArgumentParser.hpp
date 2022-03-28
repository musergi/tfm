#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class ArgumentParser {
private:
  bool argumentParsed;
  std::unordered_set<std::string> arguments;
  std::unordered_map<std::string, std::vector<std::string> > values;

  public:
  ArgumentParser();
  void addArgument(const char *name);
  void parseArgs(int argc, const char **argv);
  bool isSet(const char *arg);
  std::string getValue(const char *arg);
  std::vector<std::string> getValues(const char *arg);
};