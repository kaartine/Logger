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

#include <iostream>
#include <logger.h>

using Logs::ILogger;

int main(int /*argc*/, char ** /*argv*/) {
    ILogger *log = Logs::LoggerFactory::getLogger(Logs::CONSOLE);

    log->log(Logs::ERROR) << "Hello from test app" << std::endl;
    log->log("Another way to use logger.", Logs::WARNING);
    log->log("And some format strings. %s%d%s.", Logs::WARNING, "<", 42, ">");

    SLOGE("Here is example using MACRO: %d", 42);

    const char* debugFile = "./logs.txt";
    SLOGW("Next traces go at the end of file called %s", debugFile);

    FLOGE("This trace goes to a file.", debugFile);
    FLOGW("This as well.", debugFile);

    return 0;
}
