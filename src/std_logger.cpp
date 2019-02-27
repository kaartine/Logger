/*
MIT License

Copyright (c) 2019 Jukka Kaartinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "imp_logger.h"

#include <iostream>

namespace Logs {

void ImpStdLogger::log(const std::string &formatString, LogVerboseLevel level, ...) {

    std::string text;
    va_list args;
    va_start(args, level);
    getString(text, formatString, args);
    va_end(args);

    if (level == ERROR)
        printToStream(std::cerr, text, level);
    else if (level == WARNING)
        printToStream(std::cout, text, level);
    else
        printToStream(std::cout, text, level);

}

std::ostream &ImpStdLogger::log(LogVerboseLevel level) {
    if (level == ERROR)
        return std::cerr << "Error: ";
    else if (level == WARNING)
        return std::cout << "Warning: ";
    else
        return std::cout << "Unknown level: ";
}

}
