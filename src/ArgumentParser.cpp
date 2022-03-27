#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser():argumentParsed(false) {

}

void ArgumentParser::addArgument(const char *name) {
    arguments.push_back(name);
}

void ArgumentParser::parseArgs(int argc, const char **argv) {
    std::string last_word;
    for (int wordIndex = 0; wordIndex < argc; wordIndex++) {
        std::string word(argv[wordIndex]);
        if (word.rfind("--", 0) == 0) {
            last_word = word.substr(2);
            values[last_word];
        } else {
            values[last_word].push_back(word);
        }
    }
    argumentParsed = true;
}

bool ArgumentParser::isSet(const char *name) {
    return values.count(name);
}