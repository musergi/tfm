#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class ArgumentParser {
private:
  bool argumentParsed = false;
  std::vector<std::string> arguments;
  std::unordered_map<std::string, std::vector<std::string>> values;

public:
  ArgumentParser();
  void addArgument(const char *name);
  void parseArgs(int argc, const char **argv);
  bool isSet(const char *name);
  std::string getValue(const char *arg);
  std::vector<std::string> getValues(const char *arg);
};