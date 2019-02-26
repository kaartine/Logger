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

#include <gtest/gtest.h>

#include <logger.h>

using Logs::ILogger;
using Logs::LoggerFactory;

int countWords(std::stringstream &ss) {
    std::string word;
    int count = 0;
    while (ss >> word) {
        count++;
    }
    return count;
}

TEST (LoggerFactory, getLogger) {
    ILogger *logger = LoggerFactory::getLogger(Logs::CONSOLE);
    ASSERT_TRUE(logger);
}

TEST (Logger, init) {
    // Redirect streams
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
    std::stringstream strCout;
    std::stringstream strCerr;
    std::cout.rdbuf(strCout.rdbuf());
    std::cerr.rdbuf(strCerr.rdbuf());

    ILogger *logger = LoggerFactory::getLogger(Logs::CONSOLE);
    logger->log("Hello World!", Logs::ERROR);
    logger->log("Hello World!", Logs::WARNING);
    
    // Restore old streams
    std::cout.rdbuf(oldCoutStreamBuf);
    std::cerr.rdbuf(oldCerrStreamBuf);
    
    int count = countWords(strCout);
    EXPECT_GT(count, 0);
    count = countWords(strCerr);
    EXPECT_GT(count, 0);
}


TEST (Logger, custom_param) {
    ILogger *logger = LoggerFactory::getLogger(Logs::CONSOLE);
}

TEST (FileLogger, init_missining_file_name) {
    ILogger *logger = LoggerFactory::getLogger(Logs::FILE);
    logger->log("Hello World!", Logs::ERROR);

}
