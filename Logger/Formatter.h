#pragma once

#include <stdarg.h>
#include <string>
#include <cstring>
#include <vector>
#include <memory>

namespace Logger
{
    class DefaultFormatter
    {
            std::string _buffer;
            constexpr static const char * const _delimiter = ": ";
            
            const std::string& _format(const char *prefix, const char *format, ...)
            {
                va_list args;
                va_start(args, format);

                va_list argsCopy;
                va_copy(argsCopy, args);
                const auto len = std::vsnprintf(nullptr, 0, format, argsCopy);
                va_end(argsCopy);

                if (prefix)
                {
                    _buffer.resize(strlen(prefix) + strlen(_delimiter) + len);
                    memcpy(&_buffer[0], prefix, strlen(prefix));
                    memcpy(&_buffer[0] + strlen(prefix), _delimiter, strlen(_delimiter));
                    std::vsnprintf(&_buffer[0] + strlen(prefix) + strlen(_delimiter), _buffer.size(), format, args);
                } else {
                    _buffer.resize(len);
                    std::vsnprintf(&_buffer[0], _buffer.size(), format, args);
                }
                
                va_end(args);

                return _buffer;
            }
        public:
            template<typename... Args>
            const std::string& format(const std::string &prefix, const std::string &format, Args... args)
            {
                return _format(prefix.c_str(), format.c_str(), args...);
            }
            template<typename... Args>
            const std::string& format(const std::string &format, Args... args)
            {
                return _format(nullptr, format.c_str(), args...);
            }
    };
}

