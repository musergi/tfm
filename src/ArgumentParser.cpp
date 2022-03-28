#include "ArgumentParser.hpp"
#include <stdexcept>

ArgumentParser::ArgumentParser():argumentParsed(false) {

}

void ArgumentParser::addArgument(const char *name) {
    arguments.insert(name);
}

void ArgumentParser::parseArgs(int argc, const char **argv) {
    std::string lastWord;
    for (int wordIndex = 0; wordIndex < argc; wordIndex++) {
        std::string word(argv[wordIndex]);
        if (word.rfind("--", 0) == 0) {
            lastWord = word.substr(2);
            if (!arguments.count(lastWord)) {
                throw std::runtime_error("Invalid argument");
            }
            values[lastWord];
        } else {
            values[lastWord].push_back(word);
        }
    }
    argumentParsed = true;
}

bool ArgumentParser::isSet(const char *name) {
    return values.count(name);
}