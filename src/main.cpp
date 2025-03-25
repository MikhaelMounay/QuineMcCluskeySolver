#include <iostream>
using namespace std;

#include "logger/Logger.h"

int main() {
    Logger log(&cout);
    log << "Hello, World!\n";
    return 0;
}
