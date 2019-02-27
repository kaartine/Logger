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
#include <fstream>
#ifdef __linux__
#include <pthread.h>
#endif

using Logs::ILogger;
using Logs::LoggerFactory;

struct MyType {
    int mNumber;
    int mOtherNumber;

    friend std::ostream& operator<<(std::ostream& os, const MyType& me) {
        os << "My number: " << me.mNumber << std::endl;
        os << "My other number: " << me.mOtherNumber << std::endl;
        return os;
    }
};

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

TEST (StdLogger, basic_test) {
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

TEST (StdLogger, test_arguments) {
    // Redirect streams
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
    std::stringstream strCerr;
    std::cerr.rdbuf(strCerr.rdbuf());

    ILogger *logger = LoggerFactory::getLogger(Logs::CONSOLE);
    logger->log("Hello World %d times!", Logs::ERROR, 56);

    // Restore old streams
    std::cerr.rdbuf(oldCerrStreamBuf);

    int count = countWords(strCerr);
    EXPECT_EQ(count, 5); // "Error: Hello World 56 times!"
}

TEST (StdLogger, custom_param) {
    // Redirect streams
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
    std::stringstream strCerr;
    std::cerr.rdbuf(strCerr.rdbuf());

    MyType myType;
    myType.mNumber = 56;
    myType.mOtherNumber = 65;

    ILogger *logger = LoggerFactory::getLogger(Logs::CONSOLE);
    logger->log("Hello World! %d", Logs::ERROR, 56);
    logger->log(Logs::ERROR) << myType;

    // Restore old streams
    std::cerr.rdbuf(oldCerrStreamBuf);

    int count = countWords(strCerr);
    EXPECT_EQ(count, 12);
}

TEST (FileLogger, missining_file_name) {
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
    std::stringstream strCerr;
    std::cerr.rdbuf(strCerr.rdbuf());

    ILogger *logger = LoggerFactory::getLogger(Logs::FILE);
    logger->log("Hello World!", Logs::ERROR);

    std::cerr.rdbuf(oldCerrStreamBuf);
    int count = countWords(strCerr);
    EXPECT_GT(count, 0);
}

TEST (FileLogger, print_to_file) {
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
    std::stringstream strCerr;
    std::cerr.rdbuf(strCerr.rdbuf());

    std::string fileName = "./tmp_test_debug_logs.txt";
    remove(fileName.c_str());

    std::string text = "Hello World!";
    ILogger *logger = LoggerFactory::getLogger(Logs::FILE, fileName.c_str());
    logger->log(text.c_str(), Logs::ERROR);
    logger->log("Param: %d", Logs::WARNING, 56);

    std::cerr.rdbuf(oldCerrStreamBuf);
    int count = countWords(strCerr);
    EXPECT_EQ(count, 0);

    std::ifstream t(fileName.c_str());
    std::stringstream buffer;
    buffer << t.rdbuf();

    EXPECT_TRUE(buffer.str().find(text) != std::string::npos);
}

#ifdef __linux__
void *do_one(void * ptr);
void *do_two(void * ptr);

TEST(FileLogger, threading_test)
{
    std::string fileName = "./tmp_multithread_test_debug_logs.txt";
    remove(fileName.c_str());

    ILogger *log = LoggerFactory::getLogger(Logs::FILE, fileName.c_str());
    pthread_t mThreadID1, mThreadID2;

    ::pthread_create(&mThreadID1, nullptr, do_one, log);
    ::pthread_create(&mThreadID2, nullptr, do_two, log);

    ::pthread_join(mThreadID1, nullptr);
    ::pthread_join(mThreadID2, nullptr);
}

void *do_one(void *ptr)
{
    ILogger *log = reinterpret_cast<ILogger*>(ptr);
    int i = 0;
    while (i++ < 10000)
        log->log(Logs::ERROR) << "From thread one" << std::endl;

    return 0;
}
void *do_two(void *ptr)
{
    ILogger *log = reinterpret_cast<ILogger*>(ptr);
    int i = 0;
    while (i++ < 10000)
        log->log(Logs::ERROR) << "From thread two" << std::endl;

    return 0;
}

#endif
