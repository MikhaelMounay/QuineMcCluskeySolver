#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
using namespace std;

class Logger {
private:
    ostream* stream;

public:
    // Constructors
    Logger();
    explicit Logger(ostream* OS);

    // Operator Overloading
    template <typename T>
    Logger& operator<<(const T& a) {
        if (stream != nullptr) {
            (*stream) << a;
        }
        return *this;
    }

    Logger& operator<<(ostream& (*manip)(ostream&)) {
        if (stream != nullptr) {
            (*stream) << manip;
        }
        return *this;
    }
};

#endif //LOGGER_H
