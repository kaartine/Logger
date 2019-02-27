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

#include <string>

/**
 * Helper macros to make logging easy.
*/
#define SLOGE(string, ...) Logs::LoggerFactory::getLogger(Logs::CONSOLE)->log(string, Logs::ERROR, ##__VA_ARGS__)
#define SLOGW(string, ...) Logs::LoggerFactory::getLogger(Logs::CONSOLE)->log(string, Logs::WARNING, ##__VA_ARGS__)

#define FLOGE(string, filename, ...) Logs::LoggerFactory::getLogger(Logs::FILE, filename)->log(string, Logs::ERROR, ##__VA_ARGS__)
#define FLOGW(string, filename, ...) Logs::LoggerFactory::getLogger(Logs::FILE, filename)->log(string, Logs::WARNING, ##__VA_ARGS__)

namespace Logs {

/**
 *Logger output
*/
enum LogOutput {
    CONSOLE,    // Output to console
    FILE        // Output to file
};

/**
 *Verbose level
*/
enum LogVerboseLevel {
    ERROR,      // Only error traces
    WARNING     // Warning and error traces
};

/**
ILogger class
Is abstarct class. Implementation is created by the LoggerFactory
*/
class ILogger {
public:
    /**
     * log -function
     * C API style tracing
     *
     * @param[in] formatString      Format string
     * @param[in] level             Verbose level
     * @param[in] ...               Format string parameters
    */
    virtual void log(const std::string &formatString, LogVerboseLevel level, ...) = 0;

    /**
     * overloaded log -function
     * C++ streaming API style
     *
     * @param[in] level     Verbose level
     *
     * @return std::ostream
    */
    virtual std::ostream &log(LogVerboseLevel level) = 0;
};

/**
 *
 * LoggerFactory
 * Creates instance of ILogger. (Uses singleton design pattern)
*/
class LoggerFactory {
public:
    /**
     * getLogger
     *
     * @param[in] target    The output target
     * @param[in] fileName  Mandatory for Logs::FILE -target
     */
    static ILogger *getLogger(LogOutput target, const char *fileName = nullptr);
};

}
