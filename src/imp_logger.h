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

#pragma once

#include "logger.h"

#include <cstdarg>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdarg.h>
#include <vector>

namespace Logs {

const int error_parameters = -1;

/**
 * ImpLogger is common class for actual implementations.
 */
class ImpLogger : public ILogger {
public:
    static void getString(std::string &text, const std::string &formatString, va_list vaArgs);
    void printToStream(std::ostream &stream, std::string &text, LogVerboseLevel level);

protected:
    std::mutex mLoggerMutex;
};

/**
 * ImpStdLogger is implementation for the Logs::CONSOLE output
 *
 * Inherits ImpLogger -class
 */
class ImpStdLogger : public ImpLogger {
public:
    virtual void log(const std::string &formatString, LogVerboseLevel level, ...);
    virtual std::ostream &log(LogVerboseLevel level);
};

/**
 * ImpFileLogger is implementation for the Logs::FILE output
 *
 * Inherits ImpLogger -class
 */
class ImpFileLogger : public ImpLogger {
public:
    virtual ~ImpFileLogger();

    virtual void log(const std::string &formatString, LogVerboseLevel level, ...);
    virtual std::ostream &log(LogVerboseLevel level);

    /**
     * setFileName set output file name.
     * @param[in] fileName  File name
     */
    int setFileName(const char *fileName);

protected:
    std::string mFileName;
    std::ofstream mLogfile;
};

} // namespace
