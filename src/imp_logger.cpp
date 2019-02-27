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

void ImpLogger::getString(std::string &text, const std::string &formatString, va_list vaArgs) {
    const char * const tmpFormatString = formatString.c_str();
    va_list vaCopy;
    va_copy(vaCopy, vaArgs);
    const int inputLen = vsnprintf(nullptr, 0, tmpFormatString, vaCopy);
    va_end(vaCopy);
    std::vector<char> charVector(static_cast<size_t>(inputLen + 1));
    vsnprintf(charVector.data(), charVector.size(), tmpFormatString, vaArgs);
    text = std::string(charVector.data(), charVector.size());
}

void ImpLogger::printToStream(std::ostream &stream, std::string &text, LogVerboseLevel level) {
    if (level == ERROR)
        stream << "Error: " << text << std::endl;
    else if (level == WARNING)
        stream << "Warning: " << text << std::endl;
    else
        stream << "Unknown level: " << text << std::endl;
}

} // namespace
