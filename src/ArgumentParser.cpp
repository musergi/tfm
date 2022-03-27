#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser():argumentParsed(false) {

}

void ArgumentParser::addArgument(const char *name) {
    arguments.push_back(name);
}

void ArgumentParser::parseArgs(int argc, const char **argv) {
    for (int wordIndex = 0; wordIndex < argc; wordIndex++) {
        std::string word(argv[wordIndex]);
        if (word.rfind("--", 0) == 0) {
            values.emplace(word.substr(2));
        } else {
            values.rbegin()->second.push_back(word);
        }
    }
    argumentParsed = true;
}

bool ArgumentParser::isSet(const char *name) {
    return values.count(name);
}