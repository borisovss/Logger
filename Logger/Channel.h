#pragma once

#include <iostream>
#include <mutex>

namespace Logger
{
    class Channel
    {
        public:
            virtual ~Channel() = default;
            virtual void write(const std::string &data) = 0;
    };

    class StdOutChannel : public Channel
    {
            std::mutex _mutex;
            const bool _isThreadSafe;
        public:
            virtual ~StdOutChannel() = default;

            StdOutChannel(bool isThreadSafe = false)
            : _isThreadSafe(isThreadSafe)
            {
            }
            void write(const std::string &data) override
            {
                if (_isThreadSafe)
                {
                    _mutex.lock();
                }

                std::cout << data << std::endl;
                
                if (_isThreadSafe)
                {
                    _mutex.unlock();
                }
            }
    };
}

