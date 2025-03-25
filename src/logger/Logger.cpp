#include "Logger.h"

#include <iostream>
using namespace std;

// Static members
ostringstream Logger::_oss;

// Constructors
Logger::Logger() {
    stream = &Logger::_oss;
}

Logger::Logger(ostream* Stream) {
    stream = Stream;
}

// Getters
ostream* Logger::get_ostream() {
    return stream;
}