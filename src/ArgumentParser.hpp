#pragma once

#include <vector>
#include <string>
#include <map>

class ArgumentParser {
private:
  bool argumentParsed;
  std::vector<std::string> arguments;
  std::map<std::string, std::vector<std::string> > values;

public:
  ArgumentParser();
  void addArgument(const char *name);
  void parseArgs(int argc, const char **argv);
  bool isSet(const char *name);
  std::string getValue(const char *arg);
  std::vector<std::string> getValues(const char *arg);
};