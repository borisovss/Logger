#pragma once

#include <string>
#include <memory>

#include "Formatter.h"
#include "Channel.h"

namespace Logger
{
    template<typename Formatter = DefaultFormatter>
    class Logger
    {
        public:
            enum class Level
            {
                Trace = 0,
                Debug,
                Info,
                Warning,
                Error
            };
            Logger(const std::initializer_list<std::shared_ptr<Channel>> &channels, Level logLevel = Level::Error)
            : _currentLogLevel(logLevel),
              _channels(channels)
            {
            }
            Logger(const std::shared_ptr<Channel> &channel, Level logLevel = Level::Error)
            : _currentLogLevel(logLevel),
              _channels({channel})
            {
            }
            void addChannel(const std::shared_ptr<Channel> &channel)
            {
                _channels.push_back(channel);
            }
            template<typename... Args>
            void error(const std::string &format, Args... args)
            {
                _log(Level::Error, "Error", format, args...);
            }
            template<typename... Args>
            void warning(const std::string &format, Args... args)
            {
                _log(Level::Warning, "Warning", format, args...);
            }
            template<typename... Args>
            void info(const std::string &format, Args... args)
            {
                _log(Level::Info, "Info", format, args...);
            }
            template<typename... Args>
            void debug(const std::string &format, Args... args)
            {
                _log(Level::Debug, "Debug", format, args...);
            }
            template<typename... Args>
            void trace(const std::string &format, Args... args)
            {
                _log(Level::Trace, "Trace", format, args...);
            }
            template<typename... Args>
            void message(const std::string &format, Args... args)
            {
	            _log(nullptr, format, args...);
            }

        private:
            const Level _currentLogLevel;

            Formatter _formatter;
            std::vector<std::shared_ptr<Channel>> _channels;

            template<typename... Args>
            void _log(const char *prefix, const std::string &format, Args... args)
            {
    			const std::string *data = nullptr;
                if (prefix)
                {
                    data = &_formatter.format(prefix, format, args...);
                } else {
                    data = &_formatter.format(format, args...);
                }
    			for(auto &channel : _channels)
                {
                   	if (channel)
                   	{
                       	channel->write(*data);
                    }
                }
            }

            template<typename... Args>
    		void _log(Level level, const char *prefix, const std::string &format, Args... args)
    		{
                if (level > _currentLogLevel)
    			{
    				_log(prefix, format, args...);
    			}
    		}
    };
}

