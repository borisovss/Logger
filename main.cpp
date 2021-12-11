#include <QCoreApplication>

#include "Logger/Logger.h"
#include "Logger/Channel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Logger::Logger<> logger({std::make_shared<Logger::StdOutChannel>()}, Logger::Logger<>::Level::Info);

    //logger.addChannel(new Utils::StdOutChannel());

    logger.error("Test: %d", 5);

    return a.exec();
}
