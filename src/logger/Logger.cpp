#include "Logger.h"

#include <iostream>
using namespace std;

// Constructors
Logger::Logger() {
    stream = &_oss;
}

Logger::Logger(ostream* Stream) {
    stream = Stream;
}

// Getters
ostream* Logger::get_ostream() {
    return stream;
}

string Logger::toString() {
    return _oss.str();
}
