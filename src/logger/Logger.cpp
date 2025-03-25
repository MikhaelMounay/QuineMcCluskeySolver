#include "Logger.h"

#include <iostream>
using namespace std;

// Constructors
Logger::Logger() {
    stream = nullptr;
}

Logger::Logger(ostream* Stream) {
    stream = Stream;
}
