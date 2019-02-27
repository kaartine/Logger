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

ImpStdLogger sStdLogger;
ImpFileLogger sFileLogger;

ILogger *LoggerFactory::getLogger(LogMode mode, const char *fileName) {
    if (mode == CONSOLE) {
        return &sStdLogger;
    } else if (mode == FILE) {
        int ret = sFileLogger.setFileName(fileName);
        if (ret != 0)
            sStdLogger.log("Failed to set fileName. It might be null or path is invalid.", ERROR);
        return &sFileLogger;
    } else {
        // just for sanity
        return &sStdLogger;
    }
}

} // namespace
