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

namespace Logs {

int ImpFileLogger::setFileName(const char *fileName) {
    if (!fileName)
        return Logs::error_parameters;

    mLogfile.close();
    mLogfile.open(fileName, std::ios::out | std::ios::app);

    return 0;
}

ImpFileLogger::~ImpFileLogger() {
    mLogfile.close();
}

void ImpFileLogger::log(const std::string &formatString, LogVerboseLevel level, ...) {
    std::lock_guard<std::mutex> lock(mLoggerMutex);

    std::string text;
    va_list args;
    va_start(args, level);
    getString(text, formatString, args);
    va_end(args);

    printToStream(mLogfile, text, level);
}

std::ostream &ImpFileLogger::log(LogVerboseLevel level) {
    std::lock_guard<std::mutex> lock(mLoggerMutex);

    if (level == ERROR)
        return mLogfile << "Error: ";
    else if (level == WARNING)
        return mLogfile << "Warning: ";
    else
        return mLogfile << "Unknown level: ";
}

} // namespace
